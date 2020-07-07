#include "sortthread.h"
#include <QRandomGenerator>
#include <QDebug>


SortThread::SortThread(QObject *parent) : QObject(parent)
{
    for(int i=0;i<=500;i++){
        avgArray.append(0);
    }
    initializeArray();
}

QVector<float> SortThread::getAverage()
{
    int k=0,k1=0;
    for(int i=0;i<size;i++){
        k+=array[i];
        if((i+1)%1000==0){
            k1++;
            avgArray[k1]=(k/1000);
            k=0;
        }
    }
    return avgArray;
}

bool SortThread::activated() const
{
    return active;
}

void SortThread::initializeArray()
{
    for(int i=0;i<size;i++){
        array.push_back(QRandomGenerator::global()->generate64()%100000);
    }
    qDebug()<<"ready for work";


}

void SortThread::run()
{
    int x;
    for(int i=0; i<size; i++){
        if(active)
        for (int j=size-1; j>i;j--){
            if(array[j-1]>array[j]){
                array.swapItemsAt(j-1,j);
            }
        }
        else break;
    }
    for (auto i:array)
    setActive(false);
}

void SortThread::setActive(bool active)
{
    this->active=active;
    emit activeChanged(active);
    if(!active) emit finished();

}


