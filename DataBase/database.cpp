#include "database.h"
#include <QDebug>
#include "addtable.h"
#include <tablefield.h>
#include <QVariant>
#include <QPoint>


QString DataBase::fileName="nan.nan";

bool DataBase::updateModel(QString tableName)
{
    model->setTable(tableName);
    model->select();
}

QSqlError DataBase::request(QString request)
{
    QSqlQuery query;
    qDebug() << query.exec(request);
    return query.lastError();
}

bool DataBase::connectBD()
{
    qDebug()<<dataBase.databaseName();
    dataBase.setDatabaseName(fileName);
    return dataBase.open();
}

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    qDebug()<<"start";
}

void DataBase::setWindow(Window2 *window)
{
    this->window=window;
}

DataBase::~DataBase()
{
    qDebug() << "is closed";
    dataBase.close();
}

bool DataBase::checkDataBaseConnection(QString link)
{
    fileName=link;
    QSqlDatabase testDataBase=QSqlDatabase::addDatabase("QSQLITE");
    testDataBase.setDatabaseName(fileName);
    testDataBase.open();
    QSqlQuery query(testDataBase);
    if (query.exec("SELECT * FROM sqlite_master WHERE type = 'table'")) {
        testDataBase.close();
        return true;
    }else {query.~QSqlQuery(); return false;}
}

void DataBase::addFieldTable()
{
    if (model!=nullptr){
    TableField* tableField = new TableField(model);
    tableField->setWidjet();
    tableField->show();
    }
}

void DataBase::modeFieldTable()
{

    if(window->viewTable->currentIndex().isValid()){
        TableField* tableField = new TableField(model,window->viewTable->currentIndex());
        tableField->setWidjet();
        tableField->setInformation();
        tableField->show();
        window->viewTable->setCurrentIndex(QModelIndex());
    }
}

void DataBase::deleteFieldTable()
{
    if(window->viewTable->currentIndex().isValid()){
        QSqlQuery query(model->database());
        qDebug()<<query.exec("pragma table_info("+model->tableName()+")");
        QString exec="DELETE FROM "+model->tableName()+" WHERE (";
        while(query.next()) exec+=query.value("name").toString()+"=? and ";
        exec.replace(exec.lastIndexOf(" and "),5,");");
        query.prepare(exec);
        for(int i=0;i<model->columnCount();i++)
            query.addBindValue(model->data(model->index(window->viewTable->currentIndex().row(),i)).toString());
        qDebug()<<query.exec();
        updateModel(model->tableName());}
}

void DataBase::addTable()
{
    AddTableWindow* addTableWindow = new AddTableWindow(this);
    addTableWindow->show();
    qDebug() << "addTable-actived";
}

void DataBase::deleteTable()
{
    qDebug() << "deleteTable-actived";
    if (!window->listTables->selectedItems().isEmpty()){
        QString exec="DROP TABLE "+(window->listTables->selectedItems().front()->text());
        qDebug()<<request(exec);
        setTables();
    }
}

void DataBase::setTables()
{
        window->listTables->clear();
        tablesWidjet.clear();
        for (auto table:dataBase.tables()){
            tablesWidjet.append(new QListWidgetItem(table,window->listTables));

        }
}

void DataBase::showTable(QListWidgetItem* item){
    qDebug()<<item->text();
    model = new QSqlTableModel(this,dataBase);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    updateModel(item->text());
    connect(this,&DataBase::viewTable,window->viewTable,&QTableView::setModel);
    emit viewTable(model);
}

