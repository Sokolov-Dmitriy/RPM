#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QMenu>
#include <QColor>
#include <QString>
#include <QResizeEvent>
#include <QSize>


class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /**
     * @brief resizeRect - функция изменения размера сцены
     * @param x - координата
     * @param y - координата
     * @param size - объект класса QSize
     */
    void resizeRect(int x,int y,QSize size);

    /**
     * @brief CustomGraphicsScene - конструктор сцены
     * @param widjet - указатель на виджет где размещена сцена
     * @param parent - указатель на родительский QObject
     */
    CustomGraphicsScene(QWidget* widjet,QObject *parent = nullptr);
private:
    /**
     * @brief link - путь до файла
     */
    QString link;

    /**
     * @brief widjet - указатель на виджет где размещена сцена
     */
    QWidget *widjet;

    /**
     * @brief color - цвет кисти
     */
    QColor color;

    /**
     * @brief menu - указатель на объект контекстного меню
     */
    QMenu * menu;

    /**
     * @brief previousPoint - указатель на предыдующую точку
     */
    QPointF previousPoint;

    /**
     * @brief lastPressButton - последняя нажатая кнопка
     */
    Qt::MouseButton lastPressButton;

    /**
     * @brief contextMenuEvent - события вызова контекстного меню
     * @param event - событие
     */
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    /**
     * @brief mousePressEvent - событие нажатия на кпокку мыши
     * @param event - указатель на собитие
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;

    /**
     * @brief mouseMoveEvent - собития движения мыши
     * @param event - указатель на собитие
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private slots:
    /**
     * @brief changeRect - слот для измения размера сцены
     */
    void changeRect();

    /**
     * @brief changeColor - слот для вызова окна смены цвета
     */
    void changeColor();

    /**
     * @brief openImage - слот для вызова мокна выбора файла
     */
    void openImage();

    /**
     * @brief saveImage - слот для вызова окна выбора пути для сохранения
     */
    void saveImage();
};

#endif // CUSTOMGRAPHICSSCENE_H
