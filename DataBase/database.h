#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include "window2.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QVector>
#include <QStringList>
#include <QListWidgetItem>

class DataBase : public QObject
{
    Q_OBJECT
private:
    /**
     * @brief model - указатель на модель с таблицей
     */
    QSqlTableModel *model;
    
    /**
     * @brief tablesWidjet - массив с элементами QWidjetItem
     */
    QVector<QListWidgetItem*> tablesWidjet;
    
    /**
     * @brief window - указатель на гланвное окно
     */
    Window2* window=nullptr;
    
    /**
     * @brief dataBase - база данных
     */
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
    
public:
    /**
     * @brief updateModel - функиия обновления данные в таблице
     * @param tableName - название таблицы
     * @return - результат операции
     */
    bool updateModel(QString tableName);
    
    /**
     * @brief request - функция выполняющая запрос к базе данных
     * @param request - запрос
     * @return - ошибка или пустая строка
     */
    QSqlError request(QString request);

    /**
     * @brief connectBD - подключение к базе данных
     * @return - результат подключения
     */
    bool connectBD();

    /**
     * @brief DataBase - консткрутор класса DataBase
     * @param parent - указатель на объект класса QObject
     */
    explicit DataBase(QObject *parent = nullptr);
    
    /**
     * @brief setWindow - функция устанавливающая указатель на главное окно
     * @param window - указатель на главное окно
     */
    void setWindow(Window2* window);
    
    // десткрутор класса
    ~DataBase();
    
    /**
     * @brief fileName - статическая переменная, указываю путь к базе данных
     */
    static QString fileName;
    
    /**
     * @brief checkDataBaseConnection - функция проверкии возможности подключения к базе данных
     * @param fileName - путь до базы данных
     * @return - результат проверки
     */
    bool checkDataBaseConnection(QString fileName);
    
signals:
    /**
     * @brief viewTable - сигнал для отображения данных из таблицы
     * @param model - указатель на модель таблицы
     */
    void viewTable(QAbstractItemModel* model);
public slots:
    /**
     * @brief addFieldTable - слот для добавления нового поля в таблицу
     */
    void addFieldTable();

    /**
     * @brief modeFieldTable - слот для модификации значения в таблице
     */
    void modeFieldTable();
    
    /**
     * @brief deleteFieldTable - слот для удаления поля из таблицы
     */
    void deleteFieldTable();
    
    /**
     * @brief addTable - слот для вызова окна добавления таблицы
     */
    void addTable();
    
    /**
     * @brief deleteTable - слот для удаления таблицы
     */
    void deleteTable();
    
    /**
     * @brief setTables - функция загрузки всего списка таблиц
     */
    void setTables();
    
    /**
     * @brief showTable - функция показа таблицы
     * @param item - указатель на таблицу
     */
    void showTable(QListWidgetItem* item);
};

#endif // DATABASE_H
