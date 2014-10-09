#include "src/qmessage3_dialog.h"
#include "ui_qmessage3_dialog.h"

qmessage3_Dialog::qmessage3_Dialog(QWidget *parent, QString choose) :
    QDialog(parent),
    ui(new Ui::qmessage3_Dialog)
{
    ui->setupUi(this);

    ui->name_pushButton->setFocusPolicy(Qt::NoFocus);
    ui->number_pushButton->setFocusPolicy(Qt::NoFocus);
    ui->choose_label->setStyleSheet("QLabel {font: bold;font-size:20px;color:black;}");
    choosestr = choose;
    ui->choose_label->setText(choosestr);
}

qmessage3_Dialog::~qmessage3_Dialog()
{
    delete ui;
}

void qmessage3_Dialog::on_name_pushButton_clicked()
{
    emit sendsignal(1);
    this->close();
}

void qmessage3_Dialog::on_number_pushButton_clicked()
{
    emit sendsignal(0);
    this->close();
}

void qmessage3_Dialog::on_qmessage3_close_pushButton_clicked()
{
    this->close();
}
