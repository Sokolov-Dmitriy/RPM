#ifndef COLUMNTABLE_H
#define COLUMNTABLE_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

class ColumnTable : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief count - кол-во полей
     */
    static int count;

    /**
     * @brief fieldNameEdit - указатель на QLineEdit
     */
    QLineEdit* fieldNameEdit = new QLineEdit();

    /**
     * @brief typeComboBox - указатель на QComboBox
     */
    QComboBox* typeComboBox = new QComboBox;

    /**
     * @brief checkBoxPK - указатель на QComboBox
     */
    QCheckBox* checkBoxPK = new QCheckBox();

    /**
     * @brief checkBoxNN - указатель на QComboBox
     */
    QCheckBox* checkBoxNN = new QCheckBox();

    /**
     * @brief checkBoxAI - указатель на QComboBox
     */
    QCheckBox* checkBoxAI = new QCheckBox();

    /**
     * @brief ColumnTable - конструктор окна
     * @param fieldGridLayout - указатель на QGridLayout
     * @param parent - указатель на QObject
     */
    explicit ColumnTable(QGridLayout* fieldGridLayout,QObject *parent = nullptr);

    /**
     * @brief deleteMyself - удаление объекта
     */
    void deleteMyself();

    //деструктор окна добавления поля
    ~ColumnTable();

    /**
     * @brief setFieldInLayout - функция записи поля в layout
     */
    void setFieldInLayout();

private:
    /**
     * @brief fieldGridLayout - указатель на QGrisLayout
     */
    QGridLayout* fieldGridLayout;

    // список с аргументами поля таблицы
    QStringList typeList={"INTEGER","TEXT","BLOB","REAL","NUMERIC"};

signals:

public slots:
};

#endif // COLUMNTABLE_H
