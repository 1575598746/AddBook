#include "src/qmessage2_dialog.h"
#include "ui_qmessage2_dialog.h"
#include "src/qmessage_dialog.h"

qmessage2_Dialog::qmessage2_Dialog(QWidget *parent, QString question) :
    QDialog(parent),
    ui(new Ui::qmessage2_Dialog)
{
    ui->setupUi(this);

    ui->no_pushButton->setFocusPolicy(Qt::NoFocus);
    ui->yes_pushButton->setFocusPolicy(Qt::NoFocus);
    ui->qmessage2_label->setStyleSheet("QLabel {font: bold;font-size:20px;color:black;}");
    ques = question;
    ui->qmessage2_label->setText(ques);
}

qmessage2_Dialog::~qmessage2_Dialog()
{
    delete ui;
}

void qmessage2_Dialog::on_yes_pushButton_clicked()
{
    emit sendsignal(1);
    qmessage_Dialog *dlg = new qmessage_Dialog(0, tr("ÒÑÉ¾³ý"));
    dlg->setWindowFlags(Qt::FramelessWindowHint);
    dlg->exec();
    this->close();
}

void qmessage2_Dialog::on_no_pushButton_clicked()
{
    emit sendsignal(0);
    this->close();
}
