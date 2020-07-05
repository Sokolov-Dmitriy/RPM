#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QSqlDatabase>
#include "window2.h"
#include <QVector>




class DataBase : public QObject
{
    Q_OBJECT
private:
    QVector<QListWidgetItem*> tablesWidjet;
    Window2* window;
    QSqlDatabase dataBase=QSqlDatabase::addDatabase("QSQLITE");
//    db = QSqlDatabase::addDatabase("QSQLITE");
public:
    explicit DataBase(QObject *parent = nullptr);
    bool openDataBase();
//    void getTables();
    void setWindow(Window2* window);
//    ~DataBase();
    static QString fileName;
    bool connectDataBase(QString fileName);
public slots:
    void setTables();
    void showTable(QListWidgetItem* item);

};

#endif // DATABASE_H
