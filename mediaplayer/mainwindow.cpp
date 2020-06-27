#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
//#include <QListView>
#include <QVector>
#include <QBrush>
#include <QDebug>
#include <QIcon>
#include <QProgressBar>
#include <QSlider>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* centralWidjet = new QWidget(this);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    QHBoxLayout* hBotLayout = new QHBoxLayout(this);
    QPushButton* start = new QPushButton(this);

    QString styleButton=QString(
                "QAbstractButton {"
                "background: rgba(0,0,0,100);"
                "border-radius: 5px;"
                 "}"
                "QAbstractButton:pressed  {"
                "background: rgb(0,0,0,50);"
                "border-radius: 5px;"
                "}"
                );
    QString styleVolume = QString(
                "QSlider::handle:horizontal {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                "margin: -2px 0;"
                "width: 15px;"
                "height: 15px;"
                "border-radius: 5px;"
                "}"
                "QSlider::groove:horizontal {"
                "border: 1px solid #999999;"
                "position: absolute;"
                "border-radius: 5px;"
                "}"
                );
    QString styleBar=QString(
                "QSlider::handle:horizontal {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                "border: 2px solid rgba(46, 49, 49, 1);"
                "margin: -2px 0;"
                "width: 15px;"
                "height: 15px;"
                "border-radius: 5px;"
                "}"
                "QSlider::groove:horizontal {"
                "}"
                "QSlider::add-page:horizontal {"
                "background: rgba(248, 148, 6, 1)"
                "}"
                "QSlider::sub-page:horizontal {"
                "background: rgba(46, 49, 49, 1)"
                "}"
                );
    QVector<QIcon> icons(6);
    icons[0].addFile(":buts/buttons/play-orange.png");
    icons[1].addFile(":buts/buttons/stop-orange.png");
    icons[2].addFile(":buts/buttons/pause-orange.png");
    icons[3].addFile(":buts/buttons/skip-next-orange.png");
    icons[4].addFile(":buts/buttons/skip-previous-orange.png");
    icons[5].addFile(":buts/buttons/plus-orange.png");
    start->setIcon(icons[0]);
    start->setStyleSheet(styleButton);
    start->setIconSize(QSize(30,30));
    start->setFixedSize(QSize(40,40));
    QPushButton* stop = new QPushButton(this);
    stop->setIcon(icons[1]);
    stop->setStyleSheet(styleButton);
    stop->setIconSize(QSize(30,30));
    stop->setFixedSize(QSize(40,40));
    QPushButton* pause = new QPushButton(this);
    pause->setIcon(icons[2]);
    pause->setStyleSheet(styleButton);
    pause->setIconSize(QSize(30,30));
    pause->setFixedSize(QSize(40,40));
    QPushButton* next = new QPushButton(this);
    next->setIcon(icons[3]);
    next->setStyleSheet(styleButton);
    next->setIconSize(QSize(30,30));
    next->setFixedSize(QSize(40,40));
    QPushButton* prev = new QPushButton(this);
    prev->setIcon(icons[4]);
    prev->setStyleSheet(styleButton);
    prev->setIconSize(QSize(30,30));
    prev->setFixedSize(QSize(40,40));
    QPushButton* add = new QPushButton(this);
    add->setIcon(icons[5]);
    add->setStyleSheet(styleButton);
    add->setIconSize(QSize(30,30));
    add->setFixedSize(QSize(40,40));
    centralWidjet->setLayout(horizontalLayout);
    graphicsView = new QGraphicsView(this);
    playlistView = new QListWidget(this);
    horizontalLayout->addWidget(playlistView);
    playlistView->setFixedWidth(200);
    horizontalLayout->addLayout(gridLayout);
    gridLayout->addWidget(graphicsView,1,1,1,1);
    gridLayout->addLayout(hBotLayout,3,1,1,1);
    QHBoxLayout* addLayout = new QHBoxLayout(this);
    QHBoxLayout* centralLayout = new QHBoxLayout(this);
    QHBoxLayout* rightLayout = new QHBoxLayout(this);
    rightLayout->setAlignment(Qt::AlignRight);
    hBotLayout->addLayout(addLayout,1);
    hBotLayout->addLayout(centralLayout,6);
    hBotLayout->addLayout(rightLayout,1);
    addLayout->addWidget(add);
    centralLayout->setAlignment(Qt::AlignCenter);
    centralLayout->addWidget(prev);
    centralLayout->addWidget(pause);
    centralLayout->addWidget(start);
    centralLayout->addWidget(stop);
    centralLayout->addWidget(next);
    QPixmap img(":buts/buttons/hotpng.png");
    img=img.scaled(30,30,Qt::KeepAspectRatio);
    QSlider* volumeSlider = new QSlider(this);
    volumeSlider->setFixedWidth(100);
    volumeSlider->setFixedHeight(10);
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setStyleSheet(styleVolume);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(100);
    QLabel* volume = new QLabel(this);
    volume->setPixmap(img);
    volume->setFixedSize(30,30);
    rightLayout->addWidget(volume);
    rightLayout->addWidget(volumeSlider);
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setStyleSheet(styleBar);
    slider->setFixedHeight(12);
    gridLayout->addWidget(slider,2,1,1,1);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QColor color;
    color.setRgb(Qt::black);
    QBrush brush;
    brush.setColor(color);
    graphicsView->setBackgroundBrush(brush);
    player = new Player(this);
    graphicsView->setScene(player->getScence());
    graphicsView->show();
    graphicsView->setMinimumSize(800,600);
    player->setSize(graphicsView->size());
    player->play();
    connect(start,&QPushButton::clicked,player,&Player::play);
    connect(player,&Player::getMaxPosition,this,&MainWindow::setTime);
    connect(player,&Player::getPosition,this,&MainWindow::setPosition);
    connect(slider,&QSlider::sliderMoved,this,&MainWindow::changePosition);
    connect(volumeSlider,&QSlider::sliderMoved,this,&MainWindow::changeVolume);
    connect(stop,&QPushButton::clicked,player,&Player::stop);
    connect(pause,&QPushButton::clicked,player,&Player::pause);
    connect(next,&QPushButton::clicked,player,&Player::next);
    connect(prev,&QPushButton::clicked,player,&Player::prev);
    connect(add,&QPushButton::clicked,this,&MainWindow::addVideo);
    connect(playlistView,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(pressList(QListWidgetItem*)));
    this->setCentralWidget(centralWidjet);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setTime(int maxTime)
{
    slider->setRange(0,maxTime);

}

void MainWindow::setPosition(int time)
{
    slider->setValue(time);

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    player->setSize(graphicsView->size());

}

void MainWindow::changeVolume(int volume)
{
    player->setVolume(volume);

}

void MainWindow::changePosition(int position)
{
    player->setPosition(position*1000);

}

void MainWindow::addVideo()
{
    QStringList newList = QFileDialog::getOpenFileNames();
    for (auto link:newList){
        playlistView->addItem(new QListWidgetItem(link.right(link.size()-link.lastIndexOf("/")-1)));
        list.append(link.right(link.size()-link.lastIndexOf("/")-1));
    }
    player->setLink(newList);
}

void MainWindow::pressList(QListWidgetItem *item)
{
    int i=0;
    for(auto link:list){
        if(link.lastIndexOf(item->text())!=-1){
            time=player->playOnIndex(i);
            slider->setRange(0,time);
            return;
        }
        i++;
    }

}

