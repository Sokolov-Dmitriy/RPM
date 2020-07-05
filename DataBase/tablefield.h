#ifndef TABLEFIELD_H
#define TABLEFIELD_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QString>
#include <QGridLayout>
#include <QModelIndex>
#include <QCloseEvent>
#include <QModelIndex>
#include <QVector>
#include <QTextEdit>

class TableField : public QWidget
{
    Q_OBJECT
protected:
    /**
     * @brief closeEvent - функция перехвата события закрытия окна
     * @param event - указатель на событие
     */
    void closeEvent(QCloseEvent *event);

public:
    /**
     * @brief TableField - конструктор окна добавления/редактирования данных в поле
     * @param tableModel - указатеь на модель таблицы
     * @param index - индекс записи
     * @param parent - указатель на QWidjet
     */
    explicit TableField(QSqlTableModel* tableModel,QModelIndex index,QWidget *parent = nullptr);

    /**
     * @brief TableField - конструктор окна добавления/редактирования данных в поле
     * @param tableModel - указатеь на модель таблицы
     * @param parent - указатель на QWidjet
     */
    explicit TableField(QSqlTableModel* tableModel,QWidget *parent = nullptr);

    /**
     * @brief columnNames - вектор с названями полей
     */
    QVector<QLabel*> columnNames;

    /**
     * @brief columnText - указатель на QLineEdit
     */
    QVector<QLineEdit*> columnText;

    /**
     * @brief setInformation - функция записи в QLineEdit информации из таблицы
     */
    void setInformation();

    /**
     * @brief setWidjet - установки родительского Widjet
     */
    void setWidjet();

private:
    /**
     * @brief errorText - указатель на поле QTExtEdit
     */
    QTextEdit* errorText = new QTextEdit();

    /**
     * @brief row - номер сктроки
     */
    int row;

    /**
     * @brief tableModel - указатель на модель таблицы
     */
    QSqlTableModel* tableModel;

    /**
     * @brief index - индекс в поля в таблице
     */
    QModelIndex index;

    /**
     * @brief gridLayoyt - указатель на QGridLayout
     */
    QGridLayout* gridLayoyt = new QGridLayout(this);

    /**
     * @brief createQuery - функция запроса к таблице
     * @return - результат запроса
     */
    QSqlQuery createQuery();

signals:

public slots:
    /**
     * @brief saveEditField - слот для сохранения отредактированных данные
     */
    void saveEditField();

    /**
     * @brief saveNewField - слот для сохранения новых данных
     */
    void saveNewField();

};

#endif // TABLEFIELD_H
