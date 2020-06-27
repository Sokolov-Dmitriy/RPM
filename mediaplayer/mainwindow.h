#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>
#include <player.h>
#include <QGraphicsView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QStringList>
#include <QProgressBar>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow - конструктор главного окна
     * @param parent - указатель на лъект класса QWidjet
     */
    MainWindow(QWidget *parent = nullptr);

    //деструктор главного окна
    ~MainWindow();
protected:
    /**
     * @brief player - указатель на объект класса Player
     */
    Player* player;

    /**
     * @brief graphicsView - указаетель на виджет с видеопотоком
     */
    QGraphicsView* graphicsView;

    /**
     * @brief resizeEvent - фнкция отлова события изменения экрана
     * @param event - указатель на событие
     */
    void resizeEvent(QResizeEvent* event);

private:
    /**
     * @brief time - общее время видео
     */
    int time;

    /**
     * @brief slider - указатель на слайдер управления времени видеопотока
     */
    QSlider* slider;

    /**
     * @brief list - список с ссылками в плейлисте
     */
    QStringList list;

    /**
     * @brief playlistView - указатель на виджет с плейлистом
     */
    QListWidget* playlistView;

private slots:

    /**
     * @brief changeVolume - слот изменения громкости
     * @param volume - громкость
     */
    void changeVolume(int volume);

    /**
     * @brief changePosition - слот изменения позиции видеопотока
     * @param position - позиция
     */
    void changePosition(int position);

    /**
     * @brief setTime - слот установки длительности видеопотока
     * @param maxTime - время видеопотока
     */
    void setTime(int maxTime);

    /**
     * @brief setPosition - установка позиции видеопотока
     * @param time - позциия
     */
    void setPosition(int time);

    /**
     * @brief addVideo - слот добавления видео в плейличт
     */
    void addVideo();

    /**
     * @brief pressList - слот запуска видео из видеопотока
     * @param item - видео
     */
    void pressList(QListWidgetItem* item);

};
#endif // MAINWINDOW_H
