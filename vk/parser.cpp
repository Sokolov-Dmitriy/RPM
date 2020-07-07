#include "parser.h"
void Parser::setWindows(MainWindow *mw){
    this->mw=mw;
}

Parser::Parser(QObject *parent) : QObject(parent)
{

}

QByteArray Parser::getRequest(QUrl url)
{
    QNetworkRequest requestMy(url);
    QNetworkAccessManager manager;
    QNetworkReply *response = manager.get(requestMy);
    QEventLoop event;
    connect(response,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    disconnect(response,SIGNAL(finished()),&event,SLOT(quit()));
    return response->readAll();
}



void Parser::getFriends(QUrl url)
{
    qDebug()<< url.toString();
    listItems.clear();
    QJsonArray array=QJsonDocument::fromJson(getRequest(url)).object()["response"].toObject()["items"].toArray();
    connect(this,&Parser::changeHide,mw->listWidget,&QListWidget::setHidden);
    connect(this,&Parser::clear,mw->listWidget,&QListWidget::clear);
    emit changeHide(false);
    emit clear();
    disconnect(this,&Parser::changeHide,mw->listWidget,&QListWidget::setHidden);
    disconnect(this,&Parser::clear,mw->listWidget,&QListWidget::clear);
    for (auto i:array)
        listItems.append(new QListWidgetItem(i.toObject()["first_name"].toString()+" "+i.toObject()["last_name"].toString(),mw->listWidget));
}

void Parser::writeContent(int buttonNumber,QJsonValue value,QString text)
{
    connect(this,&Parser::changeHide,mw->contentLabels+buttonNumber,&QLabel::setHidden);
    connect(this,&Parser::setText,mw->contentLabels+buttonNumber,&QLabel::setText);
    if(!(value.toString()=="")){
        emit setText(text+value.toString());
        emit changeHide(false);
    }else emit changeHide(true);
    disconnect(this,&Parser::changeHide,mw->contentLabels+buttonNumber,&QLabel::setHidden);
    disconnect(this,&Parser::setText,mw->contentLabels+buttonNumber,&QLabel::setText);
}

void Parser::downloadPhoto(QString link)
{
    QUrl url=QUrl(link);
    QString fileName =QCoreApplication::applicationDirPath()+ "/avatar.jpg";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(getRequest(url));
    file.close();
    mw->setImage(fileName,mw->contentLabels+6);
}



QUrl Parser::createQUrl(QString id,int type)
{
    if(type==0) return QUrl("https://api.vk.com/method/users.get?user_ids="+id+
    "&fields=id,first_name,last_name,photo_100,is_closed,bdate,deactivated,nickname,sex&access_token=66e9623c1ac304676e7eb0aa2f045eaf3ea21583e8951f5a359ed800bffc13609bfad34fae2c8c07d716e&v=5.103");
    else return QUrl("https://api.vk.com/method/friends.get?user_id="+id+
    "&fields=first_name,last_name&access_token=66e9623c1ac304676e7eb0aa2f045eaf3ea21583e8951f5a359ed800bffc13609bfad34fae2c8c07d716e&v=5.103");
}

void Parser::postRequest(QUrl url){
        QJsonObject jsonOb = QJsonDocument::fromJson(getRequest(url)).object()["response"].toArray().first().toObject();
        writeContent(1,jsonOb["first_name"],"Имя:");
        writeContent(2,jsonOb["last_name"],"Фамилия:");
        writeContent(3,jsonOb["nickname"],"Ник:");
        writeContent(5,jsonOb["bdate"],"День рождения:");
        downloadPhoto(jsonOb["photo_100"].toString());
        getFriends(createQUrl(QString::number(jsonOb["id"].toInt()),1));
}


void Parser::getId(QString id){
    this->id=id;
}

void Parser::postId(){
    postRequest(createQUrl(id,0));
}
