#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customgraphicsscene.h"
#include <QMainWindow>
#include <QString>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow - конструктор главного окнв
     * @param parent - указатель на родительский QWidjet
     */
    MainWindow(QWidget *parent = nullptr);

    //деструктор главного окна
    ~MainWindow();
protected:
    /**
     * @brief resizeEvent - собитие измения размера окна
     * @param event - указатель на событие
     */
    void resizeEvent(QResizeEvent *event);
private:
    /**
     * @brief scene - указатель на графическую сцену
     */
    CustomGraphicsScene* scene;
public slots:
    /**
     * @brief setImage слот установки изображения
     * @param link - путь до изображения
     */
    void setImage(QString link);
};
#endif // MAINWINDOW_H
