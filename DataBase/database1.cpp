#include "database1.h"
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>
#include <QListWidgetItem>

QString DataBase::fileName="nan.nan";



DataBase::DataBase(QObject *parent):QObject(parent)
{

}

bool DataBase::openDataBase()
{
    dataBase.setDatabaseName(fileName);
    dataBase.open();
    return true;
}

//void DataBase::getTables()
//{

//    if (dataBase.isOpen()){
//        QSqlQuery query(dataBase);
//        qDebug() << query.exec("SELECT * FROM sqlite_master WHERE type = 'table'");

//        while(query.next()){

//            qDebug() << query.value(1).toString();
//            new QListWidgetItem(query.value(1).toString(),window->listTables);
//        }

//    }

//        dataBase.close();
//}

void DataBase::setWindow(Window2 *window)
{
    this->window=window;
}

//DataBase::~DataBase()
//{
//    dataBase.close();
//}

bool DataBase::connectDataBase(QString link)
{
    fileName=link;
//    return true;

    dataBase.setDatabaseName(fileName);
    dataBase.open();
    QSqlQuery query(dataBase);
    if (query.exec("SELECT * FROM sqlite_master WHERE type = 'table'")) {
        dataBase.close();
        return true;
    }else return false;
}

void DataBase::setTables()
{
    if (dataBase.isOpen()){
        window->listTables->clear();
        tablesWidjet.clear();
//        dataBase.tables();
//        QSqlQuery query(dataBase);
//        qDebug() << query.exec("SELECT * FROM sqlite_master WHERE type = 'table'");
        for (auto table:dataBase.tables()){
//            qDebug()<<table;
            tablesWidjet.append(new QListWidgetItem(table,window->listTables));

        }
//        while(query.next()){

//            qDebug() << query.value(1).toString();
//            new QListWidgetItem(query.value(1).toString(),window->listTables);
//        }

    }

        dataBase.close();
}

void DataBase::showTable(QListWidgetItem* item){
    //        window->listTables->indexWidget(index);
    qDebug()<<item->text();
}
