#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    widjet = new QWidget(this);
    this->setCentralWidget(widjet);
    vLayout = new QVBoxLayout(widjet);
    tableWidget = new QTableWidget(widjet);
    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(columnCount);
    QPushButton* addCulumnBut = new QPushButton("добавить столбец",widjet);
    QPushButton* addRowBut = new QPushButton("добавить строку",widjet);
    QPushButton* saveTable = new QPushButton("сохранить таблицу",widjet);
    QPushButton* cleanBut = new QPushButton("очистить выделенные ячейки",widjet);
    QHBoxLayout* hButLayout = new QHBoxLayout(widjet);
    hButLayout->addWidget(addRowBut);
    hButLayout->addWidget(addCulumnBut);
    hButLayout->addWidget(cleanBut);
    connect(addCulumnBut,&QPushButton::clicked,this,&MainWindow::addColumn);
    connect(addRowBut,&QPushButton::clicked,this,&MainWindow::addRow);
    connect(saveTable,&QPushButton::clicked,this,&MainWindow::save);
    connect(cleanBut,&QPushButton::clicked,this,&MainWindow::clean);
    vLayout->addLayout(hButLayout);
    vLayout->addWidget(tableWidget);
    vLayout->addWidget(saveTable);
    widjet->setFixedSize(1000,500);
    widjet->setLayout(vLayout);
}

void MainWindow::openExcel()
{
    excel = new QAxObject("Excel.Application", this);
    workbooks = excel->querySubObject("Workbooks");
    workbook = workbooks->querySubObject("Open(const QString&)", QFileDialog::getOpenFileNames());
    sheets = workbook->querySubObject("Sheets");
    sheet = sheets->querySubObject("Item(int)", 1);
}

void MainWindow::writeInExcel()
{
    for(int i=0;i<rowCount;i++)
        for(int j=0;j<columnCount;j++){
            QAxObject* cell = sheet->querySubObject("Cells(int,int)", i+1, j+1);
            if(tableWidget->item(i,j)!=0) cell->setProperty("Value",QVariant(tableWidget->item(i,j)->data(0)));
            else cell->setProperty("Value"," ");
            delete cell;
        }
}

void MainWindow::closeExcel()
{
    workbook->dynamicCall("Save()");
    delete sheet;
    delete sheets;
    delete workbook;
    delete workbooks;
    excel->dynamicCall("Quit()");
    delete excel;
}

MainWindow::~MainWindow()
{

}

void MainWindow::addColumn()
{
    columnCount+=1;
    tableWidget->setColumnCount(columnCount);
}

void MainWindow::addRow()
{
    rowCount+=1;
    tableWidget->setRowCount(rowCount);
}

void MainWindow::save()
{
    openExcel();
    writeInExcel();
    closeExcel();

}

void MainWindow::clean()
{
    for(int i=0;i<rowCount;i++){
        for(int j=0;j<columnCount;j++){
            if(tableWidget->item(i,j)!=0)
                if(tableWidget->item(i,j)->isSelected())
                    tableWidget->item(i,j)->setText(" ");
        }
    }
}

