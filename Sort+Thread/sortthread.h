#ifndef SORTTHREAD_H
#define SORTTHREAD_H

#include <QObject>
#include <QTimer>
#include <QBarSet>

class SortThread : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SortThread - класс для сортировки и работы в одтельном потоке
     * @param parent - указатель на родительский класс
     */
    explicit SortThread(QObject *parent = nullptr);

    /**
     * @brief getAverage - функций получения массива со средними значениями
     * @return - массив по средними значениями
     */
    QVector<float> getAverage();

    /**
     * @brief active - булевое значение, обозначающее работает ли сортировка
     */
    bool active;

    /**
     * @brief activated - функция, возвращающая работает ли сортировка
     * @return
     */
    bool activated() const;

    /**
     * @brief array - массив со значениями для сортировки
     */
    QVector<int> array;

    /**
     * @brief avgArray - массив со средними значениями
     */
    QVector<float> avgArray;

    /**
     * @brief initializeArray - функция инициализации массива начальными значениями
     */
    void initializeArray();

    /**
     * @brief size - размер массива
     */
    int size = 500000;
private:


signals:
    /**
     * @brief finished - сигнал остановки сортировки
     */
    void finished();

    /**
     * @brief activeChanged - сигнал изменения сигнала работы потока
     * @param active - сигнал работы
     */
    void activeChanged(bool active);
public slots:
    /**
     * @brief run - слот запуска сортировки
     */
    void run();

    /**
     * @brief setActive - функция установки значения запуска
     * @param active - true/false
     */
    void setActive(bool active);
};

#endif // SORTTHREAD_H
