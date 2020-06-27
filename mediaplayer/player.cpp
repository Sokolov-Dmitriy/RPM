#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setPlaylist(playlist);
    videoItem = new QGraphicsVideoItem;
    player->setVideoOutput(videoItem);
    scence = new QGraphicsScene;
    scence->addItem(videoItem);
    connect(player,&QMediaPlayer::positionChanged,this,&Player::mediaChanged);
}

QGraphicsScene *Player::getScence()
{
    return scence;
}


void Player::setLink(QStringList links)
{
    for(auto link:links)
        playlist->addMedia(QUrl::fromLocalFile(link));
}

void Player::setSize(QSize size)
{
    videoItem->setSize(size);
}

QSize Player::getSize()
{
    videoItem->size();
}

int Player::playOnIndex(int index)
{
    playlist->setCurrentIndex(index);
    player->play();
    return player->duration()/1000;
}

void Player::setPosition(int position)
{
    player->setPosition(position);
}

void Player::setVolume(int volume)
{
    player->setVolume(volume);
}


void Player::mediaChanged(qint64 position)
{
    time=position/1000;
    emit getMaxPosition(player->duration()/1000);
    emit getPosition(time);
    qDebug()<<position/1000;
    qDebug()<<player->duration()/1000;


}

void Player::play()
{
    player->play();

}

void Player::stop()
{
    player->stop();

}

void Player::pause()
{
    player->pause();

}

void Player::next()
{
    playlist->next();

}

void Player::prev()
{
    playlist->previous();

}
