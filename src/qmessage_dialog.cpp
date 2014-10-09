#include "src/qmessage_dialog.h"
#include "ui_qmessage_dialog.h"

qmessage_Dialog::qmessage_Dialog(QWidget *parent, QString strname) :
    QDialog(parent),
    ui(new Ui::qmessage_Dialog)
{
    ui->setupUi(this);

    ui->qmessage_pushButton->setFocusPolicy(Qt::NoFocus);
    ui->qmessage_label->setStyleSheet("QLabel {font: bold;font-size:20px;color:black;}");

    str=strname;
    ui->qmessage_label->setText(str);

    connect(ui->qmessage_pushButton, SIGNAL(clicked()), this, SLOT(window_close()));
}

qmessage_Dialog::~qmessage_Dialog()
{
    delete ui;
}

void qmessage_Dialog::window_close()
{
    this->close();
}
