#ifndef ADDTABLE_H
#define ADDTABLE_H
#include <columntable.h>
#include <QWidget>
#include <QCloseEvent>
#include <QTextEdit>
#include <QLabel>
#include "database.h"

class AddTableWindow : public QWidget
{
    Q_OBJECT
protected:
    /**
     * @brief closeEvent - функция перехвата события закрытия окна
     * @param event - указатель на событие
     */
    void closeEvent(QCloseEvent *event);

public:
    // дестркутор
    ~AddTableWindow();

    /**
     * @brief AddTableWindow - конструктор окна создания новой таблицы
     * @param database - указатель на базу данных
     * @param parent - указатель на родительский QWidjet
     */
    explicit AddTableWindow(DataBase* database,  QWidget *parent = nullptr);

private:
    /**
     * @brief createTableExec - функция обработки запроса к базе данных
     * @return - результат запроса
     */
    QString createTableExec();

    /**
     * @brief codeErrorText - указаель на QTextEdit
     */
    QTextEdit* codeErrorText = new QTextEdit();

    /**
     * @brief tableName - название таблицы
     */
    QString tableName;

    /**
     * @brief fields - вектор с полями таблицы
     */
    std::vector<ColumnTable*> fields;

    /**
     * @brief lables - вектор с объектами QLable
     */
    QVector<QLabel*> lables;

    /**
     * @brief fieldGridLayout - указатль на QGridLayout
     */
    QGridLayout* fieldGridLayout = new QGridLayout();

    /**
     * @brief database - указатель на объект базы данных
     */
    DataBase* database;
signals:

public slots:
    /**
     * @brief changeNameTable - слот для смены названия таблицы
     * @param name - название таблицы
     */
    void changeNameTable(QString name);

    /**
     * @brief addField - слот для добавления нового поля в таблицу
     */
    void addField();

    /**
     * @brief save - слот для сохрания таблицы
     */
    void save();
};

#endif // ADDTABLE_H
