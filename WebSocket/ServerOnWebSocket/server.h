#ifndef SERVER_H
#define SERVER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QAction>
#include <QString>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QApplication>


class Server : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Server - констуктор класса Server
     * @param parent - укзатель на родительский объект класса QObject
     */
    explicit Server(QObject *parent = nullptr);
    /**
     * @brief showCommands - функция вывода всех команд для управления сервером
     */
    void showCommands();
    /**
     * @brief ~Server - деструктор класса Server
     */
    virtual ~Server();
private:
    /**
     * @brief loadSettings - загрузка начальный праметров из ini файлв
     */
    void loadSettings();
    /**
     * @brief saveSettings - запись параметров в ini файл
     */
    void saveSettings();
    /**
     * @brief start - запуск сервера
     */
    void start();
    /**
     * @brief changePort - фунция измения номера порта
     * @param port - номер порта
     */
    void changePort(int port);
    /**
     * @brief restart - функция перезапуска сервера
     */
    void restart();
    /**
     * @brief loadMessageFromDataBase - загрузка последний 10 сообщений из базы данных
     */
    void loadMessageFromDataBase();
    /**
     * @brief loadMessageToDataBase - запись последний 10 сообщений в базу данных
     */
    void loadMessageToDataBase();
    /**
     * @brief sendLastMessage - отправка клиенту послений 10 сообщений
     * @param client - указатель на QWebSocket клиента
     */
    void sendLastMessage(QWebSocket* client);
    /**
     * @brief connectClientToSystem - функция добавления клиента в список всех клиентов
     * @param client - указатель на QWebSocket клиента
     */
    void connectClientToSystem(QWebSocket* client);
    /**
     * @brief sendMessage - отправка сообщения клиенту
     * @param byteArray - сообщение в виде массива байтов
     */
    void sendMessage(QByteArray byteArray);
    /**
     * @brief createMessage - функция преобразования сообщения в массив байтов
     * @param nick - ник клиента
     * @param message - сообщение
     * @return - массив байтов
     */
    QByteArray createMessage(QString nick,QString message);
    /**
     * @brief saveMessage - функция сохрания сообщения
     * @param byteArray - массив байтов
     */
    void saveMessage(QByteArray byteArray);
    /**
     * @brief clients контейнер Map для храения информации о подключенных клиентах
     */
    QMap<QString,QWebSocket*> clients;
    /**
     * @brief webServer - указатель на объект класса QWebSocketServer
     */
    QWebSocketServer* webServer=nullptr;
    /**
     * @brief messages - Json массив с последними 10 сообщениями
     */
    QJsonArray messages;
    /**
     * @brief port - номер установленного порта
     */
    int port=2000;
    /**
     * @brief serverName - имя сервера
     */
    QString serverName;
    /**
     * @brief databaseMacros - макрос базы данных
     */
    QString databaseMacros;
    /**
     * @brief tableStruct - запрос на создания таблицы в базе данных
     */
    QString tableStruct;

signals:
    /**
     * @brief signalExit - сигнал закрытия сервера
     */
    void signalExit();
    /**
     * @brief writeToConsole - сигнал записи инфрмации в консоль
     * @param line - информация для записи
     */
    void writeToConsole(QString line);
public slots:
    /**
     * @brief close - слот для закрытия сервера
     */
    void close();
    /**
     * @brief runCommand - слот для обработки комманд
     * @param command - команда
     */
    void runCommand(QString command);
    /**
     * @brief connectClient - слот для обработки подключения нового пользователя
     */
    void connectClient();
    /**
     * @brief getByteArray - слот для обработки нового сообщения на сервер
     * @param byteArray - массив байтов
     */
    void getByteArray(QByteArray byteArray);
    /**
     * @brief disconnectedClient - слот для обработки отключения клиента
     */
    void disconnectedClient();

};

#endif // SERVER_H
