#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QWidget"
#include "QTableWidget"
#include "QPushButton"
#include "QString"
#include "QFileDialog"
#include <ActiveQt/qaxobject.h>
#include <ActiveQt/qaxbase.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief excel - указатель на Excel
     */
    QAxObject* excel;

    /**
     * @brief workbooks - указатель на книги
     */
    QAxObject* workbooks;

    /**
     * @brief workbook - указатель на директорию, откуда грузить книг
     */
    QAxObject* workbook;

    /**
     * @brief sheets - указатель на список листов
     */
    QAxObject* sheets;

    /**
     * @brief sheet - указатель на рабочий лист
     */
    QAxObject* sheet ;

    /**
     * @brief tableWidget - указатель на таблицу
     */
    QTableWidget* tableWidget;

    /**
     * @brief vLayout - общий layout
     */
    QVBoxLayout* vLayout;

    /**
     * @brief widjet - указатель на главный QWidjet
     */
    QWidget* widjet;

    /**
     * @brief rowCount - кол-во строк
     */
    int rowCount=1;

    /**
     * @brief columnCount - кол-во столбцов
     */
    int columnCount=1;

    /**
     * @brief link - путь до excel файла
     */
    QString link;

    /**
     * @brief MainWindow - конструктор главного окна
     * @param parent - указатель на родительский объект
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief openExcel - функция открытия excel файла
     */
    void openExcel();

    /**
     * @brief writeInExcel - функция записи в excel файл
     */
    void writeInExcel();

    /**
     * @brief closeExcel - функция закрытия и сохранения excel файла
     */
    void closeExcel();

    //деструктор главного окна
    ~MainWindow();
public slots:
    /**
     * @brief addColumn - слот добавления новой колонки в таблицу
     */
    void addColumn();

    /**
     * @brief addRow - слот добавления новой строки в таблицу
     */
    void addRow();

    /**
     * @brief save - слот сохранени данных excel файл
     */
    void save();

    /**
     * @brief clean - слот очистки выделенных ячеек
     */
    void clean();

private:

};
#endif // MAINWINDOW_H
