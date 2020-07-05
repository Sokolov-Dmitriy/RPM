#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QPushButton"
#include "QVector"
#include "QSize"
#include "QPixmap"
#include "QLabel"
#include "QFileDialog"
#include <QDebug>
#include "database.h"
#include "window2.h"
#include <QCoreApplication>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setContentsMargins(0,-80,0,0);
    QWidget* wgt = new QWidget();
    QSize sizeButton(100,50);
    QPixmap img(":/img/sqlLogo.png");
    img=img.scaled(200,150,Qt::KeepAspectRatio);
    QVector<QPushButton*> buttons;
    QLabel* logo = new QLabel();
    logo->setPixmap(img);
    buttons.append(new QPushButton("Открыть"));
    buttons.append(new QPushButton("Создать"));
    QVBoxLayout* vLayout = new QVBoxLayout(wgt);
//    QPushButton* createDataBase = new QPushButton();
    vLayout->addWidget(logo);
    QHBoxLayout* hLayout = new QHBoxLayout();
    vLayout->addLayout(hLayout);
    for (auto button:buttons){
        hLayout->addWidget(button);
        button->setFixedSize(sizeButton);
    }
    connect(buttons[0],&QPushButton::clicked,this,&MainWindow::openDataBaseFile);
    connect(buttons[1],&QPushButton::clicked,this,&MainWindow::newDataBase);
    this->setCentralWidget(wgt);
}

MainWindow::~MainWindow()
{
    qDebug()<<"del";
    delete ui;
}

void MainWindow::changeHiden()
{
    this->setHidden(false);
}

void MainWindow::openDataBaseFile(){


    QString fileName=QFileDialog::getOpenFileName(this,"Open DataBase","/home/dmitriy/Рабочий стол","SQLite File (*.sqlite *.sqlite3)");
    DataBase dataBase;
    if(dataBase.checkDataBaseConnection(fileName) && fileName!=""){
        Window2* window = new Window2;
        connect(window,&Window2::destroyed,this,&MainWindow::changeHiden);
        window->show();
        this->setHidden(true);
    }
}

void MainWindow::newDataBase()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save DataBase","/home/dmitriy/Рабочий стол","SQLite File (*.sqlite *.sqlite3)");
    if(fileName.indexOf(".sqlite" || ".sqlite3")) fileName+=".sqlite3";
    qDebug()<<fileName;
    DataBase dataBase;
    if(dataBase.checkDataBaseConnection(fileName) && fileName!=""){
        Window2* window = new Window2;
        connect(window,&Window2::destroyed,this,&MainWindow::changeHiden);
        window->show();
        this->setHidden(true);
    }
}
