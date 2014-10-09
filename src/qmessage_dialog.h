#ifndef QMESSAGE_DIALOG_H
#define QMESSAGE_DIALOG_H

#include <QDialog>

namespace Ui {
class qmessage_Dialog;
}

class qmessage_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit qmessage_Dialog(QWidget *parent = 0, QString strname = "");
    ~qmessage_Dialog();
    
private:
    Ui::qmessage_Dialog *ui;
    QString str;

private slots:
    void window_close();
};

#endif // QMESSAGE_DIALOG_H
