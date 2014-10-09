#ifndef QMESSAGE3_DIALOG_H
#define QMESSAGE3_DIALOG_H

#include <QDialog>

namespace Ui {
class qmessage3_Dialog;
}

class qmessage3_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit qmessage3_Dialog(QWidget *parent = 0, QString choose = "");
    ~qmessage3_Dialog();

signals:
    void sendsignal(bool);
    
private slots:
    void on_name_pushButton_clicked();

    void on_number_pushButton_clicked();

    void on_qmessage3_close_pushButton_clicked();

private:
    Ui::qmessage3_Dialog *ui;
    QString choosestr;
};

#endif // QMESSAGE3_DIALOG_H
