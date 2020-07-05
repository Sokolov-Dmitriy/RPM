#include "window2.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QPushButton>
#include <QFrame>
#include <QBoxLayout>
#include "database.h"
#include <QDebug>


Window2::~Window2()
{
    qDebug()<<"win2 deleted";
}

Window2::Window2(QWidget *parent) : QWidget(parent)
{
    DataBase* dataBase=new DataBase();
    dataBase->connectBD();
    dataBase->setWindow(this);
    QGridLayout* gridLayout = new QGridLayout();
    QFrame* frameLeftTop = new QFrame();
    gridLayout->addWidget(frameLeftTop,1,1,1,1);
    QHBoxLayout* hLeftTopLayout = new QHBoxLayout();
    frameLeftTop->setLayout(hLeftTopLayout);
    frameLeftTop->setFrameShape(QFrame::Box);
    frameLeftTop->setLineWidth(5);
    QPushButton* saveAndReturn = new QPushButton("Save and Ret");
    hLeftTopLayout->addWidget(saveAndReturn);
    saveAndReturn->setFixedSize(QSize(166,40));
    connect(saveAndReturn,&QPushButton::clicked,dataBase,&DataBase::deleteLater);
    connect(dataBase,&DataBase::destroyed,this,&Window2::deleteLater);
    QFrame* frameLeftBottom = new QFrame();
    gridLayout->addWidget(frameLeftBottom,2,1,1,1);
    QVBoxLayout* vLeftBottomLayout = new QVBoxLayout();
    frameLeftBottom->setLayout(vLeftBottomLayout);
    frameLeftBottom->setFrameShape(QFrame::Box);
    frameLeftBottom->setLineWidth(5);
    QHBoxLayout* tableOptionsLayout = new QHBoxLayout();
    vLeftBottomLayout->addLayout(tableOptionsLayout);
    QVector<QPushButton*> tableOptionsButs;
    tableOptionsButs.append(new QPushButton("Add"));
    tableOptionsButs.append(new QPushButton("Del"));
    for (auto but:tableOptionsButs){
        tableOptionsLayout->addWidget(but);
        but->setFixedSize(QSize(80,40));
    }
    connect(tableOptionsButs[0],&QPushButton::clicked,dataBase,&DataBase::addTable);
    connect(tableOptionsButs[1],&QPushButton::clicked,dataBase,&DataBase::deleteTable);
    vLeftBottomLayout->addWidget(listTables);
    listTables->setFixedHeight(400);
    emit dataBase->setTables();
    connect(listTables,&QListWidget::itemDoubleClicked,dataBase,&DataBase::showTable);
    QFrame* frameCentralBottom = new QFrame();
    gridLayout->addWidget(frameCentralBottom,2,2,2,1);
    QHBoxLayout* CentralBottomLayout = new QHBoxLayout();
    frameCentralBottom->setLayout(CentralBottomLayout);
    frameCentralBottom->setFrameShape(QFrame::Box);
    frameCentralBottom->setLineWidth(5);
    viewTable->setFixedWidth(600);
    viewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    CentralBottomLayout->addWidget(viewTable);
    viewTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    viewTable->setSelectionMode(QAbstractItemView::SingleSelection);
    QVector<QPushButton*> editTableBut;
    editTableBut.append(new QPushButton("Add"));
    editTableBut.append(new QPushButton("Mod"));
    editTableBut.append(new QPushButton("Del"));
    connect(editTableBut[0],&QPushButton::clicked,dataBase,&DataBase::addFieldTable);
    connect(editTableBut[1],&QPushButton::clicked,dataBase,&DataBase::modeFieldTable);
    connect(editTableBut[2],&QPushButton::clicked,dataBase,&DataBase::deleteFieldTable);
    QVBoxLayout* hEditTableLayout = new QVBoxLayout();
    CentralBottomLayout->addLayout(hEditTableLayout);
    hEditTableLayout->setAlignment(Qt::AlignTop);
    for (auto but:editTableBut){
        hEditTableLayout->addWidget(but);
        but->setFixedSize(QSize(80,40));
    }
    this->setLayout(gridLayout);
}

//void Window2::selectTablee(const QModelIndex &index)
//{
//    qDebug()<<index.isValid();
//}
