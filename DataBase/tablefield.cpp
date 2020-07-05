#include "tablefield.h"
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QPushButton>
#include <QtSql/QSqlError>


void TableField::closeEvent(QCloseEvent *event)
{
    delete this;
    event->accept();
}

TableField::TableField(QSqlTableModel* tableModel,QModelIndex index,QWidget *parent) :
    row(index.row()), tableModel(tableModel), index(index), QWidget(parent){
    QPushButton* saveEditBut = new QPushButton("Save");
    gridLayoyt->addWidget(saveEditBut,3,1);
    connect(saveEditBut,&QPushButton::clicked,this,&TableField::saveEditField);
    this->setLayout(gridLayoyt);
}

TableField::TableField(QSqlTableModel* tableModel,QWidget *parent):
    tableModel(tableModel), QWidget(parent){
    QPushButton* saveNewBut = new QPushButton("Save");
    gridLayoyt->addWidget(saveNewBut,3,1);
    connect(saveNewBut,&QPushButton::clicked,this,&TableField::saveNewField);
    this->setLayout(gridLayoyt);
}

void TableField::setInformation()
{
    for(int i=0;i<columnText.size();i++)
        columnText[i]->setText(tableModel->data(tableModel->index(row,i)).toString());
}

void TableField::setWidjet()
{
    QSqlQuery query(tableModel->database());
    qDebug()<<query.exec("pragma table_info("+tableModel->tableName()+")");
    int i=0;
    while(query.next()){
        columnNames.append(new QLabel(query.value("name").toString()));
        columnText.append(new QLineEdit());
        gridLayoyt->addWidget(columnNames[i],1,i+1);
        gridLayoyt->addWidget(columnText[i],2,i+1);
        i++;
    }
}

void TableField::saveEditField()
{
    for(int column=0;column<columnText.size();column++)
        tableModel->setData(tableModel->index(row,column),QVariant::fromValue(columnText[column]->text()));
    errorText->setText(tableModel->lastError().text());
    gridLayoyt->addWidget(errorText,4,1,1,columnText.size());
    if(tableModel->submit()) closeEvent(new QCloseEvent);
    else{
        errorText->setText(tableModel->lastError().text());
        gridLayoyt->addWidget(errorText,4,1,1,columnText.size());
    }
}

QSqlQuery TableField::createQuery()
{
    QSqlQuery query(tableModel->database());
    QString exec;
    for(auto name:columnNames) exec+=name->text()+",";
    exec=exec.replace(exec.lastIndexOf(","),1,"")+") VALUES (";
    for(auto name:columnNames) exec+=":"+name->text()+",";
    exec="INSERT INTO "+tableModel->tableName()+" ("+exec.replace(exec.lastIndexOf(","),1,"")+");";
    query.prepare(exec);
    for(int i=0;i<columnText.size();i++) query.bindValue(i,columnText[i]->text());
    return query;
}

void TableField::saveNewField()
{
    QSqlQuery query = createQuery();
    if(query.exec()){
        tableModel->setTable(tableModel->tableName());
        tableModel->select();
        closeEvent(new QCloseEvent);
    }
    else{
        errorText->setText(query.lastError().text());
        gridLayoyt->addWidget(errorText,4,1,1,columnText.size());
    }
}


