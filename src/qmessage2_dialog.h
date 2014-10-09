#ifndef QMESSAGE2_DIALOG_H
#define QMESSAGE2_DIALOG_H

#include <QDialog>

namespace Ui {
class qmessage2_Dialog;
}

class qmessage2_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit qmessage2_Dialog(QWidget *parent = 0, QString question = "");
    ~qmessage2_Dialog();
signals:
    void sendsignal(bool);

    
private slots:
    void on_yes_pushButton_clicked();

    void on_no_pushButton_clicked();

private:
    Ui::qmessage2_Dialog *ui;

    QString ques;
};

#endif // QMESSAGE2_DIALOG_H
