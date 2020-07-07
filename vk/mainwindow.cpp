#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <Qt>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <parser.h>
#include <QListWidget>
#include <QListWidgetItem>

void MainWindow::setImage(QString link,QLabel* label)
{
    QPixmap img(link);
    img=img.scaled(*size,Qt::KeepAspectRatio);
    label->setPixmap(img);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Parser* parser = new Parser();
    parser->setWindows(this);

    QWidget* wgt = new QWidget();

    QGridLayout* layout = new QGridLayout(wgt);
    QHBoxLayout* hLayout = new QHBoxLayout();
    QHBoxLayout* hContent = new QHBoxLayout();
    QVBoxLayout* vTextContent = new QVBoxLayout();

    QLabel* logo = new QLabel();
    logo->setAlignment(Qt::AlignHCenter);
//    setImage(".."+QApplication::applicationFilePath()+"/vk.png",logo);
    setImage(":/new/logo/vk.png",logo);

    QLineEdit* idEdit = new QLineEdit();
    QLabel* vkID = new QLabel("ID");
    QPushButton* getBotton = new QPushButton("Получить");

    layout->addWidget(logo,1,1,1,4);
    layout->addLayout(hLayout,2,1,1,4);

    hLayout->addWidget(vkID);
    hLayout->addWidget(idEdit);
    hLayout->addWidget(getBotton);

    layout->addLayout(hContent,3,1,1,4);
    hContent->addLayout(vTextContent);
    layout->addWidget(listWidget,4,1,1,4);

    listWidget->setFixedHeight(100);
    listWidget->setHidden(true);

    for (int i=0;i<6;i++) {
        vTextContent->addWidget(contentLabels+i);
        contentLabels[i].setHidden(true);
    }
    hContent->addWidget(contentLabels+6);

    connect(getBotton,&QPushButton::clicked,parser,&Parser::postId);
    connect(idEdit,&QLineEdit::textChanged,parser,&Parser::getId);
    this->setCentralWidget(wgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
