#ifndef PARSER_H
#define PARSER_H

#include <mainwindow.h>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QtNetwork/QtNetwork>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrl>
#include <QVector>
#include <QEventLoop>
#include <QCoreApplication>

class Parser : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief setWindows - функция получения указателя на главное окно приложения
     * @param mw - указатель на главное окно приложения
     */
    void setWindows(MainWindow* mw);

    /**
     * @brief Parser - конструктор класса
     * @param parent - указатель на родительский объект
     */
    explicit Parser(QObject *parent = nullptr);
private:
    /**
     * @brief getRequest - функция расшифровки запросов
     * @param url - https запрос
     * @return - информация из ответа в виде массива байтов
     */
    QByteArray getRequest(QUrl url);

    /**
     * @brief listItems - список друзей пользователя
     */
    QVector<QListWidgetItem*> listItems;

    /**
     * @brief getFriends - функция получения списка друзей
     * @param url - https запрос на получение списка друзей
     */
    void getFriends(QUrl url);

    /**
     * @brief mw - указатель на главное окно
     */
    MainWindow* mw;

    /**
     * @brief writeContent
     * @param buttonNumber
     * @param value
     * @param text
     */
    void writeContent(int buttonNumber,QJsonValue value,QString text);

    /**
     * @brief downloadPhoto - функция скачиваня фото
     * @param link - ссылка на фотографию
     */
    void downloadPhoto(QString link);

    /**
     * @brief createQUrl - функция создания запросов
     * @param id - id пользователя
     * @param type - тип запроса
     * @return - запрос
     */
    QUrl createQUrl(QString id,int type=0);

    /**
     * @brief postRequest - функция создания запроса на сервер
     * @param url - https запрос
     */
    void postRequest(QUrl url);

    /**
     * @brief id - id пользователя
     */
    QString id;
signals:
    /**
     * @brief clear - сиглнал очистки списка друзей старого запроса
     */
    void clear();

    /**
     * @brief loadPhoto - сигнал записи фото
     */
    void loadPhoto();

    /**
     * @brief changeHide
     * @param signal
     */
    void changeHide(bool signal);

    /**
     * @brief setText - сигнал записи данных
     * @param text - текст
     */
    void setText(QString text);
public slots:

    /**
     * @brief getId - слот передачи id
     * @param id - id пользователя
     */
    void getId(QString id);

    /**
     * @brief postId - слот отправки id в запрос
     */
    void postId();
};

#endif // PARSER_H
