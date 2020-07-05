#ifndef WINDOW2_H
#define WINDOW2_H

#include <QWidget>
#include <QListWidget>
#include <QTableView>
#include <QModelIndex>

class Window2 : public QWidget
{
    Q_OBJECT
public:
    //Деструктор главного окна
    ~Window2();

    /**
     * @brief listTables - список с таблицами
     */
    QListWidget* listTables = new QListWidget();

    /**
     * @brief viewTable - указатель на объект класса QTableView
     */
    QTableView* viewTable = new QTableView();

    /**
     * @brief Window2 - конструктор главного окна
     * @param parent - указатель на родительский класс QWidjet
     */
    explicit Window2(QWidget *parent = nullptr);

private:

signals:

public slots:
    /**
     * @brief selectTablee
     * @param index
     */
//    void selectTablee(const QModelIndex &index);

};

#endif // WINDOW2_H
