#include "columntable.h"
#include <QDebug>

ColumnTable::ColumnTable(QGridLayout* fieldGridLayout,QObject *parent) : fieldGridLayout(fieldGridLayout),QObject(parent)
{
    typeComboBox->addItems(typeList);
    count++;
}

void ColumnTable::deleteMyself()
{
    delete this;
}

ColumnTable::~ColumnTable()
{
    qDebug()<<"del";
    count--;
    delete fieldNameEdit;
    delete typeComboBox;
    delete checkBoxAI;
    delete checkBoxNN;
    delete checkBoxPK;
}

void ColumnTable::setFieldInLayout()
{
    fieldGridLayout->addWidget(fieldNameEdit,count+1,1);
    fieldGridLayout->addWidget(typeComboBox,count+1,2);
    fieldGridLayout->addWidget(checkBoxNN,count+1,3);
    fieldGridLayout->addWidget(checkBoxPK,count+1,4);
    fieldGridLayout->addWidget(checkBoxAI,count+1,5);
}
int ColumnTable::count=0;
