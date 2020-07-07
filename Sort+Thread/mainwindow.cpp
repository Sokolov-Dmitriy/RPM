#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    threadSort = new QThread();
    sortThread = new SortThread();

    ui->setupUi(this);
    view = new QChartView(this);
    ui->verticalLayout->addWidget(view);
    chart = new QChart();
    series = new QBarSeries();
    sortThread->moveToThread(threadSort);
    set = new QBarSet("This");
    for(int i=0;i<500;i++){
        set->append(i+100000);
    }
    QColor col;
    col.setRgb(255,0,0);
    set->setColor(col);
    timer = new QTimer();
    connect(timer,&QTimer::timeout, this, &MainWindow::setValues);
    series->append(set);
    chart->addSeries(series);
    chart->setTitle("Среднее значение по сортировке");
    createAxisX();
    createAxisY();
    view->setRenderHint(QPainter::Antialiasing);
    view->setChart(chart);
    connect(ui->start,&QPushButton::clicked,this,&MainWindow::start);
    connect(ui->exit,&QPushButton::clicked,this,&MainWindow::exit);
    connect(threadSort, &QThread::started, sortThread, &SortThread::run);
    connect(sortThread, &SortThread::finished, threadSort, &QThread::terminate);
    connect(ui->start,&QPushButton::clicked,this,&MainWindow::setDisable);
    connect(sortThread,&SortThread::finished,this,&MainWindow::setEnable);

}

void MainWindow::createAxisX()
{
    QStringList categories;
    for(int i=1;i<=500;i++)
        categories.append(QString::number(i));
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
}

void MainWindow::createAxisY()
{
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Среднее");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    sortThread->setActive(true);
    threadSort->start();
    timer->start(3000);
}

void MainWindow::exit()
{
    sortThread->setActive(false);
    this->close();
}

void MainWindow::setValues()
{
    int k=0;
    for(auto i:sortThread->getAverage()){
        set->replace(k,i);
        k++;
    }

    series->insert(0,set);
}

void MainWindow::setDisable()
{
    ui->start->setDisabled(true);
}

void MainWindow::setEnable()
{
    ui->start->setDisabled(false);

}

