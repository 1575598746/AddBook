#ifndef DIALOG_H
#define DIALOG_H

#include "src/getdatabase.h"
#include <QtSql>
#include <QSqlQueryModel>
#include <QListWidgetItem>
#include <QTimer>
#include <QLCDNumber>
#include <QTimeEdit>
#include <QRect>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QDesktopWidget>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void initlistWidget();

signals:
    void isCurrentTime();
    
private slots:
    void on_insert_pushButton_clicked();

    void on_delete_pushButton_clicked();

    void on_modify_pushButton_clicked();

    void on_select_pushButton_clicked(); 

    void listWidget_item_click();

    void receivesig(bool a);

    void receivesig_1(bool a);

    void on_quit_pushButton_clicked();

    void clockChange();

    void comToCur();

    void dialogUp();

    void down();

    //void mini();




private:
    Ui::Dialog *ui;

    QSqlQueryModel *model;

    QTimer *timer;
    QTimer *uptimer;
    QTimer *dtimer;
    QTimer *itimer;


    QAction *showAct;
    QAction *quitAct;
    QMenu *trayIconMenu;

    QRect rect;

    QSystemTrayIcon *trayIcon;
    int x;
    int y;


};

#endif // DIALOG_H
