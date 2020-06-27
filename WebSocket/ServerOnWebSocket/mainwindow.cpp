#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QAction>

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"___________________________________";
    trayIcon->show();
    this->setHidden(true);
    event->ignore();
}

void MainWindow::createTrayIcon()
{
    trayIcon = new QSystemTrayIcon(QIcon(":/imgs/logo2.png"),this);
    trayIconMenu = new QMenu("Options",this);
    QAction * closeServer = new QAction(QIcon(":/imgs/close.png"),"Close Server", this);
    QAction * openTerminal = new QAction(QIcon(":/imgs/expand.png"),"Open", this);
    connect(closeServer,&QAction::triggered,this,&MainWindow::exit);
    connect(openTerminal,&QAction::triggered,this,&MainWindow::openUp);
    trayIconMenu->addAction(openTerminal);
    trayIconMenu->addAction(closeServer);
    trayIcon -> setContextMenu(trayIconMenu);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    server = new Server(this);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::send);
    connect(ui->lineEdit,&QLineEdit::textChanged,this,&MainWindow::setCommand);
    connect(server,&Server::writeToConsole,this,&MainWindow::write);
    connect(ui->pushButton,&QPushButton::clicked,ui->lineEdit,&QLineEdit::clear);
    ui->textEdit->setReadOnly(true);
    connect(server,&Server::signalExit,this,&MainWindow::exit);
    server->showCommands();
    createTrayIcon();
}

MainWindow::~MainWindow()
{
//    server->deleteLater();
//    delete ui;
//    delete trayIcon;
//    delete trayIconMenu;
//    server->deleteLater();
}

void MainWindow::exit()
{
    qDebug()<<"exit";
//    delete server;
//    server->close();
    server->deleteLater();
    deleteLater();
}

void MainWindow::openUp()
{
    this->show();
    trayIcon->hide();
}

void MainWindow::hideInTray()
{
    trayIcon->show();
    this->setHidden(true);
}

void MainWindow::send()
{
    emit server->runCommand(command);
}

void MainWindow::setCommand(QString command)
{
    this->command=command;
}

void MainWindow::write(QString line)
{
    qDebug()<<line;
    ui->textEdit->append(line);
}

