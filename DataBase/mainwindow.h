#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow - конструктор начального окна
     * @param parent - указатель на объект класса QWidjet
     */
    explicit MainWindow(QWidget *parent = 0);

    //Деструктор главного окна
    ~MainWindow();

public slots:
    /**
     * @brief changeHiden - слот для скрытия начального окна
     */
    void changeHiden();

    /**
     * @brief openDataBaseFile - слот для вызова окна выбора файла с базой данных
     */
    void openDataBaseFile();

    /**
     * @brief newDataBase - слот для вызова окна для сохрания новой базы данных
     */
    void newDataBase();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
