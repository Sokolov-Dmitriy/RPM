#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QtMultimediaWidgets/QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QString>
#include <QMediaContent>
class Player : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Player - конструктор класса Player
     * @param parent - указатель на объект класса QObject
     */
    explicit Player(QObject *parent = nullptr);

    /**
     * @brief getScence - функция получения указаетеля на графическую сцену
     * @return - указаетель на графическую сцену
     */
    QGraphicsScene* getScence();

    /**
     * @brief setLink - функция добавления видео в плейлист
     * @param links - список с ссылками на видео
     */
    void setLink(QStringList links);

    /**
     * @brief setSize - установка размера сцены
     * @param size - размер
     */
    void setSize(QSize size);

    /**
     * @brief getSize - получения размера сцены
     * @return - размер
     */
    QSize getSize();

    /**
     * @brief playOnIndex - запуск видео из плейлиста
     * @param index - индекс в плейлисте
     * @return - позиция
     */
    int playOnIndex(int index);

    /**
     * @brief setPosition -
     * @param position
     */
    void setPosition(int position);

    /**
     * @brief setVolume
     * @param volume
     */
    void setVolume(int volume);

private:
    /**
     * @brief time
     */
    int time;

    /**
     * @brief playlist
     */
    QMediaPlaylist* playlist;

    /**
     * @brief player
     */
    QMediaPlayer* player;

    /**
     * @brief scence
     */
    QGraphicsScene* scence;

    /**
     * @brief videoItem
     */
    QGraphicsVideoItem *videoItem;

signals:
    /**
     * @brief getPosition - сигнал передачи позиции видеопотока
     * @param time - позиция
     */
    void getPosition(int time);

    /**
     * @brief getMaxPosition - сигнал передачи максимальной длины видеопотока
     * @param maxTime - длина
     */
    void getMaxPosition(int maxTime);

public slots:
    /**
     * @brief mediaChanged - слот изменения позиции видеопотока
     * @param position - позиция
     */
    void mediaChanged(qint64 position);

    /**
     * @brief play - слот запуска видеопотока
     */
    void play();

    /**
     * @brief stop - слот остановки видеопотока
     */
    void stop();

    /**
     * @brief pause - слот установки видеопотока на паузу
     */
    void pause();

    /**
     * @brief next - слот переход на след видео
     */
    void next();

    /**
     * @brief prev - слот перехода на предыдущее видео из плейлиста
     */
    void prev();

};

#endif // PLAYER_H
