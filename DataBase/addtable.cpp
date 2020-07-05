#include "addtable.h"
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QVector>

AddTableWindow::~AddTableWindow()
{
    qDebug()<<"addTablw window was daleted";
}

AddTableWindow::AddTableWindow(DataBase* database, QWidget *parent) : database(database),QWidget(parent)
{
    QGridLayout* gridLayout = new QGridLayout(parent);
    QLineEdit* lineEdit = new QLineEdit();
    connect(lineEdit,&QLineEdit::textChanged,this,&AddTableWindow::changeNameTable);
    QLabel* tableNameLable = new QLabel("Table name:");
    QPushButton* addField = new QPushButton("Add Field");
    connect(addField,&QPushButton::clicked,this,&AddTableWindow::addField);
    gridLayout->addWidget(tableNameLable,1,1);
    gridLayout->addWidget(lineEdit,1,2,1,4);
    gridLayout->addWidget(addField,2,1);
    gridLayout->addLayout(fieldGridLayout,3,1,1,5);
    lables.append(new QLabel("name"));
    lables.append(new QLabel("type"));
    lables.append(new QLabel("NN"));
    lables.append(new QLabel("PK"));
    lables.append(new QLabel("AI"));
    for(auto i=0;i<lables.size();i++){
        fieldGridLayout->addWidget(lables[i],1,i+1);
        lables[i]->setHidden(true);
    }
    QPushButton* saveBut = new QPushButton("Save");
    gridLayout->addWidget(codeErrorText,4,1,1,4);
    codeErrorText->setFixedHeight(50);
    gridLayout->addWidget(saveBut,4,5,1,1);
    connect(saveBut,&QPushButton::clicked,this,&AddTableWindow::save);
    this->setLayout(gridLayout);
}


void AddTableWindow::changeNameTable(QString name)
{
    tableName=name;
}

void AddTableWindow::addField()
{
    if(ColumnTable::count==0)
        for(auto lable:lables)
            lable->setHidden(false);
    fields.push_back(new ColumnTable(fieldGridLayout));
    fields.back()->setFieldInLayout();

}

QString AddTableWindow::createTableExec()
{
    QString exec="CREATE TABLE "+tableName+" (";
    for(int i=0;i<fields.size();i++){
        exec+=fields[i]->fieldNameEdit->text();
        exec+=" "+fields[i]->typeComboBox->currentText();
        exec+=(fields[i]->checkBoxNN->isChecked())?" NOT NULL":"";
        exec+=(fields[i]->checkBoxPK->isChecked())?" PRIMARY KEY":"";
        exec+=(fields[i]->checkBoxAI->isChecked())?" AUTOINCREMENT":"";
        exec+=",";}
    exec.replace(exec.lastIndexOf(","),1,"");
    if(fields.empty()) exec.replace("("||")","");
    return exec.append(");").replace(QString("()"),QString(""));
}

void AddTableWindow::save()
{
    QString text=database->request(createTableExec()).text();
    if(text==" " || text==""){
        emit database->setTables();
        closeEvent(new QCloseEvent);
    }else emit codeErrorText->setText(text);
}

void AddTableWindow::closeEvent(QCloseEvent *event){
    for (auto field_:fields){
        field_->deleteMyself();
    }
    deleteLater();
    event->accept();
}
