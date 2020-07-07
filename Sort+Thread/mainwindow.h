#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtCharts/QChart>
#include <QtCharts>
#include <QThread>
#include <QTimer>
#include "sortthread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
using namespace QtCharts;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief set - набор значений для диаграммы
     */
    QBarSet *set;

    /**
     * @brief timer - указатель на объект класса QTimer
     */
    QTimer *timer;

    /**
     * @brief series - указатель на диаграмму
     */
    QBarSeries *series;

    /**
     * @brief createAxisX - функция создания оси X
     */
    void createAxisX();

    /**
     * @brief createAxisY - функция создания оси Y
     */
    void createAxisY();

    /**
     * @brief view - указатель на объект класса QChartView
     */
    QChartView* view;

    /**
     * @brief chart - указаьель на объект класса QChart
     */
    QChart* chart;

    /**
     * @brief MainWindow - контруктор главного окна
     * @param parent - указатель на родительский класс
     */
    MainWindow(QWidget *parent = nullptr);

    //деструктор
    ~MainWindow();
public slots:
    /**
     * @brief start - слот для обработки кнопки "start"
     */
    void start();

    /**
     * @brief exit - слот для обработки кнопки "start"
     */
    void exit();

    /**
     * @brief setValues - слот для установки значений в диаграмму
     */
    void setValues();

    /**
     * @brief setDisable - слот установки кнопки "start" неактивной
     */
    void setDisable();

    /**
     * @brief setEnable - слот установки кнопки "start" активной
     */
    void setEnable();
private:
    /**
     * @brief threadSort - указатель на объект клаcса QThread
     */
    QThread* threadSort;

    /**
     * @brief sortThread - указатель на объект класса SortThread
     */
    SortThread* sortThread;

    /**
     * @brief ui - указатель на формы
     */
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
