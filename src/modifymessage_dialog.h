#ifndef MODIFYMESSAGE_DIALOG_H
#define MODIFYMESSAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class modifymessage_Dialog;
}

class modifymessage_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit modifymessage_Dialog(QWidget *parent = 0, QString modify = "", QString modify_1 = "", QString modify_2 = "");
    ~modifymessage_Dialog();
    
private slots:
    void on_confirm_pushButton_clicked();

private:
    Ui::modifymessage_Dialog *ui;

    QString modifystr;

    QString modify_1_str;

    QString modify_2_str;
};

#endif // MODIFYMESSAGE_DIALOG_H
