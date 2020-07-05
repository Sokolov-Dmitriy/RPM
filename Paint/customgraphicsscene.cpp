#include "customgraphicsscene.h"
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QList>

CustomGraphicsScene::CustomGraphicsScene(QWidget* widjet,QObject *parent):QGraphicsScene(parent),widjet(widjet)
{
    connect(this,&CustomGraphicsScene::sceneRectChanged,this,&CustomGraphicsScene::changeRect);
    menu = new QMenu();
    QList<QAction*> actions={new QAction("Color", this),new QAction("Open image", this),new QAction("Save as", this)};
    connect(actions[0],&QAction::triggered,this,&CustomGraphicsScene::changeColor);
    connect(actions[1],&QAction::triggered,this,&CustomGraphicsScene::openImage);
    connect(actions[2],&QAction::triggered,this,&CustomGraphicsScene::saveImage);
    menu->addActions(actions);
}

void CustomGraphicsScene::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    menu->exec(QCursor::pos());
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    lastPressButton=event->button();
    if(lastPressButton==Qt::LeftButton){
    addEllipse(event->scenePos().x() - 5,
               event->scenePos().y() - 5,
               10, 10,
               QPen(Qt::NoPen),
               QBrush(color));
    previousPoint = event->scenePos();
    }
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(lastPressButton==Qt::LeftButton){
        addLine(previousPoint.x(),
               previousPoint.y(),
               event->scenePos().x(),
               event->scenePos().y(),
               QPen(color,10,Qt::SolidLine,Qt::RoundCap));
       previousPoint = event->scenePos();
    }
}

void CustomGraphicsScene::resizeRect(int x,int y,QSize size)
{
    this->setSceneRect(x,y,size.width()-20,size.height()-20);
}

void CustomGraphicsScene::changeRect()
{
    qDebug()<<"<<<<<<<<<";
}

void CustomGraphicsScene::changeColor()
{
    QColorDialog colorDialog;
    color = colorDialog.getColor();
}

void CustomGraphicsScene::openImage()
{
    QFileDialog fileDialog;
    link=fileDialog.getOpenFileName(widjet,"Open Image","/","Images (*.png *.xpm *.jpg)");
    QPixmap pixmap(link);
    this->setSceneRect(0,0,pixmap.width(),pixmap.height());
    this->addPixmap(pixmap);
}

void CustomGraphicsScene::saveImage()
{
    QFileDialog fileDialog;
    link=fileDialog.getSaveFileName(widjet,"Save Image","/","Images (*.png *.xpm *.jpg)");
    QImage image(this->width(), this->height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(NULL);
    QPainter painter(&image);
    this->render(&painter);
    image.save(link);
}
