#include "server.h"



Server::Server(QObject *parent) : QObject(parent)
{
    loadSettings();
    loadMessageFromDataBase();
}

void Server::start()
{
    if(webServer==nullptr){
    webServer = new QWebSocketServer(serverName,QWebSocketServer::NonSecureMode,this);
    webServer->listen(QHostAddress::Any,port);
    if (webServer->isListening()){
        emit writeToConsole("Server started!");
        emit writeToConsole("URL:"+webServer->serverUrl().toString()+"\n");
    }
    else emit writeToConsole("ERROR\n");
    connect(webServer,&QWebSocketServer::newConnection,this,&Server::connectClient);
    }
}

void Server::close()
{
    if(webServer!=nullptr){
        webServer->close();
        webServer->deleteLater();
        webServer=nullptr;
        emit writeToConsole("Server is disabled!\n");
    } emit writeToConsole("Server is not running!\n");
}

void Server::changePort(int port)
{
    if(port > 1023 and port <= 65535){
        this->port=port;
        if (webServer!=nullptr){
            emit writeToConsole("Server is running now! To save You can use");
            emit writeToConsole("COMMAND: restart\n");
        } else
            emit writeToConsole("The port was changed!\n");
    }
}

void Server::restart()
{
    if(webServer!=nullptr){
        close();
        start();
    }else writeToConsole("Server is not running!");
}

void Server::showCommands()
{
    emit writeToConsole("The curent port number:"+QString::number(port));
    emit writeToConsole("To change port number you can use");
    emit writeToConsole("COMMAND: change port [port number]\n");

    emit writeToConsole("To run server you can use");
    emit writeToConsole("COMMAND: start\n");

    emit writeToConsole("To stop server you can use");
    emit writeToConsole("COMMAND: stop\n");

    emit writeToConsole("To exit you can use(server stops automatically)");
    emit writeToConsole("COMMAND: exit\n");
}

Server::~Server()
{
    close();
    loadMessageToDataBase();
    saveSettings();
    qDebug()<<"-_-_-_-_-_-_-_-_-_-";
}

void Server::loadSettings()
{
    QSettings settings(QApplication::applicationDirPath()+"/settings.ini",QSettings::IniFormat,this);
    port=settings.value("port",2000).toInt();
    QSettings startSettings(":/ini/startSettings.ini",QSettings::IniFormat,this);
    serverName = startSettings.value("serverName").toString();
    databaseMacros = startSettings.value("databaseMacros").toString();
    tableStruct = startSettings.value("tableStruct").toString();
}

void Server::saveSettings()
{
    QSettings settings(QApplication::applicationDirPath()+"/settings.ini",QSettings::IniFormat,this);
    settings.setValue("port",port);
}

void Server::loadMessageFromDataBase()
{
    QSqlDatabase database=QSqlDatabase::addDatabase(databaseMacros);
    database.setDatabaseName(QApplication::applicationDirPath()+"/message.sqlite3");
    database.open();
    QSqlQuery query(database);
    if(database.tables().empty()) qDebug()<<query.exec(tableStruct);
    else{
        query.exec("SELECT * FROM messages");
        while(query.next()) saveMessage(createMessage(query.value("nick").toString(),query.value("message").toString()));
    }
    database.close();
}

void Server::loadMessageToDataBase()
{
    QSqlDatabase database=QSqlDatabase::addDatabase(databaseMacros);
    database.setDatabaseName(QApplication::applicationDirPath()+"/message.sqlite3");
    database.open();
    QSqlQuery query(database);
    query.exec("delete from messages;");
    for(auto value:messages){
        query.prepare("INSERT INTO messages VALUES (?,?)");
        query.bindValue(0,value.toObject()["nick"].toString());
        query.bindValue(1,value.toObject()["message"].toString());
        query.exec();
    }
    database.close();
}

void Server::sendLastMessage(QWebSocket *client)
{
    QJsonDocument doc(messages);
    client->sendBinaryMessage(doc.toJson());
}

void Server::connectClientToSystem(QWebSocket *client)
{
    connect(client,&QWebSocket::binaryMessageReceived,this,&Server::getByteArray);
    connect(client,&QWebSocket::disconnected,this,&Server::disconnectedClient);
}

void Server::sendMessage(QByteArray byteArray)
{
    QJsonArray array;
    array.append(QJsonDocument::fromJson(byteArray).object());
    QJsonDocument docc(array);
    for(auto client:clients){
        client->sendBinaryMessage(docc.toJson());
    }

}

QByteArray Server::createMessage(QString nick, QString message)
{
    QJsonObject object;
    object["nick"]=nick;
    object["message"]=message;
    QJsonDocument doc(object);
    return doc.toJson();
}

void Server::saveMessage(QByteArray byteArray)
{
    messages.append(QJsonDocument::fromJson(byteArray).object());
    if (messages.size()>10){
        messages.removeFirst();
    }
}

void Server::runCommand(QString command)
{
    if (command=="start") start();
    if (command=="stop") close();
    if (command == "restart") restart();
    if (command == "exit") emit signalExit();
    if (command.section(" ",0,1)=="change port") changePort(command.section(" ",2,3).toInt());
}

void Server::connectClient()
{
    QWebSocket* connection = webServer->nextPendingConnection();
    QString nick = connection->requestUrl().toString().section("login=",1,1);
    if (clients.find(nick)==clients.end()){
        sendMessage(createMessage(nick,"was connected"));
        clients[nick]=connection;
        connectClientToSystem(connection);
        writeToConsole("user:"+nick+" was connected");
        connection->sendBinaryMessage(QJsonDocument(messages).toJson());
    }
    else connection->close();
}

void Server::getByteArray(QByteArray byteArray)
{
    sendMessage(byteArray);
    saveMessage(byteArray);
    qInfo()<<"messages were send:"<< QJsonDocument::fromJson(byteArray).object();
}



void Server::disconnectedClient()
{
    for(auto client:clients){
        if(!client->isValid()){
            writeToConsole("user:"+client->requestUrl().toString().section("login=",1,1)+" was disconnected");
            sendMessage(createMessage(client->requestUrl().toString().section("login=",1,1),"was disconnected!"));
            clients.remove(client->requestUrl().toString().section("login=",1,1));
            break;
        }
    }
}
