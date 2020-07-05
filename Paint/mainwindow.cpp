#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QApplication>
#include <QDebug>
#include <QGridLayout>
#include <QGraphicsView>
#include <QWidget>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget * widjet = new QWidget(this);
    this->setCentralWidget(widjet);
    QGridLayout* gridLayout = new QGridLayout(this);
    QGraphicsView* graphicsView = new QGraphicsView(this);
    gridLayout->addWidget(graphicsView);
    scene = new CustomGraphicsScene(this);
    qDebug()<<QApplication::applicationDirPath()<<"/Cat03.jpg";
    this->setMinimumSize(800,400);
    graphicsView->setScene(scene);
    widjet->setLayout(gridLayout);
}


MainWindow::~MainWindow()
{
    //    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    scene->resizeRect(this->x(),this->y(),this->size());
}

void MainWindow::setImage(QString link)
{
    QPixmap image(link);
    scene->addPixmap(image);
}

