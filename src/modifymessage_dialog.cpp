#include "src/modifymessage_dialog.h"
#include "ui_modifymessage_dialog.h"
#include "src/qmessage_dialog.h"


#include <QSqlQuery>
#include <qDebug>

modifymessage_Dialog::modifymessage_Dialog(QWidget *parent, QString modify, QString modify_1, QString modify_2) :
    QDialog(parent),
    ui(new Ui::modifymessage_Dialog)
{
    ui->setupUi(this);

    ui->confirm_pushButton->setFocusPolicy(Qt::NoFocus);
    //ui->nameNum_label->setStyleSheet("QLabel {font: bold;font-size:20px;color:black;}");
    //ui->numName_label->setStyleSheet("QLabel {font: bold;font-size:20px;color:black;}");
    modifystr = modify;
    modify_1_str = modify_1;
    modify_2_str = modify_2;
    ui->numName_label->setText(modifystr);
    ui->nameNum_label->setText(modify_1_str);
    ui->numName_lineEdit->setText(modify_2_str);
}

modifymessage_Dialog::~modifymessage_Dialog()
{
    delete ui;
}

void modifymessage_Dialog::on_confirm_pushButton_clicked()
{
    QSqlQuery query;
    QString sql = "update AddBook set ";
    sql += modify_1_str+" = '";
    sql += ui->nameNum_lineEdit->text()+"'";
    sql += " where ";
    sql += modifystr;
    sql += " = '";
    sql += ui->numName_lineEdit->text()+"'";

    QString sql1 = "select * from AddBook where ";
    sql1 += modify_1_str+" = '";
    sql1 += ui->nameNum_lineEdit->text()+"'";
    query.exec(sql1);

    if(ui->nameNum_lineEdit->text().isEmpty()||ui->numName_lineEdit->text().isEmpty())
    {
          qmessage_Dialog *a = new qmessage_Dialog(0,tr("信息不能为空！"));
          a->setWindowFlags(Qt::FramelessWindowHint);
          a->exec();
    }
    else if(query.next())
    {
        qmessage_Dialog *a = new qmessage_Dialog(0,tr("此信息已存在！"));
        a->setWindowFlags(Qt::FramelessWindowHint);
        a->exec();
        this->close();
    }
    else
    {
        qDebug()<<sql;
        query.exec(sql);
        //initlistWidget();
        this->close();
    }


}
