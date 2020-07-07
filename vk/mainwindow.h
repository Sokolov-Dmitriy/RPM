#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QString>
#include <QSize>
#include <QLabel>
#include <QListWidget>
#include <QCoreApplication>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief contentLabels - массив для форм с данными
     */
    QLabel *contentLabels = new QLabel[7];

    /**
     * @brief setImage - функция установки автарки
     * @param link - ссылка на фото
     * @param label - форма для картинки
     */
    void setImage(QString link,QLabel* label);

    /**
     * @brief MainWindow - конструктор главного окга
     * @param parent - указатель на родительский класс
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief listWidget - лист с виджетами для списка друзей
     */
    QListWidget* listWidget = new QListWidget();

    //
    ~MainWindow();
private:
    /**
     * @brief size - размер картинки
     */
    QSize *size = new QSize(100,100);

    /**
     * @brief ui - указатель на графический интерфейс
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
