#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QSystemTrayIcon>
#include "server.h"
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    /**
     * @brief closeEvent - переопределение функции closeEvent
     * @param event - событие закрытия
     */
    void closeEvent(QCloseEvent *event);
private:
    /**
     * @brief server - указатель на класс сервера
     */
    Server* server;
    /**
     * @brief command - команды с консоли
     */
    QString command;
    /**
     * @brief trayIcon - класс иконки в трее
     */
    QSystemTrayIcon* trayIcon;
    /**
     * @brief trayIconMenu - класс меню для икоки в трее
     */
    QMenu *trayIconMenu;
    /**
     * @brief createTrayIcon - функция переноса приложения в трей
     */
    void createTrayIcon();
public:
    /**
     * @brief ui - указатель на редактор форм
     */
    Ui::MainWindow *ui;
    /**
     * @brief MainWindow - констуктор главного окна
     * @param parent - указатель на родительский класс QWidjet
     */
    MainWindow(QWidget *parent = nullptr);
    //деструктор главного окна
    ~MainWindow();

public slots:
    /**
     * @brief exit - слот для обработки команды выхода
     */
    void exit();
    /**
     * @brief openUp - слот для открытия приложения из треи
     */
    void openUp();
    /**
     * @brief hideInTray - слот для сворачивания приложения в трей
     */
    void hideInTray();
    /**
     * @brief send - слот для считывания команды
     */
    void send();
    /**
     * @brief setCommand - ослот для отправки команды на сервер
     * @param command - команда
     */
    void setCommand(QString command);
    /**
     * @brief write - слот для записи информаци в консоль приложения
     * @param line - иформация для записи
     */
    void write(QString line);

};
#endif // MAINWINDOW_H
