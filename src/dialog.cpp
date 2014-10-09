#include "src/dialog.h"
#include "ui_dialog.h"
#include "src/qmessage_dialog.h"
#include "src/qmessage2_dialog.h"
#include "src/qmessage3_dialog.h"
#include "src/modifymessage_dialog.h"

#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQueryModel>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    getDataBase mydatabase;
    mydatabase.createConnection("AddBook.db3");
    mydatabase.createTables();
    mydatabase.createDatabase();

    //ui->insert_pushButton->setStyleSheet("background:rgba(0,0,0,0%);");
    ui->insert_pushButton->setFocusPolicy(Qt::NoFocus);

    ui->timeSet_pushButton->setFocusPolicy(Qt::NoFocus);

    ui->lcdNumber->setStyleSheet("background:rgba(0,0,0,0%);");

    //ui->timeEdit->setStyleSheet("background:rgba(0,0,0,0%);");

    ui->tabWidget->setFocusPolicy(Qt::NoFocus);
    ui->tabWidget->setStyleSheet(
                "QTabBar::tab{background:rgba(0,0,0,0%);padding:12px;}"
                "QTabBar::tab:selected{background:#0868f8;}"
                "QTabWidget::pane{border:1;}"
                "QWidget{background: rgba(0,0,0,0%);}");

    ui->linkman_listWidget->setStyleSheet("QListWidget {font:bold; font-size:20px; color:green; background:rgba(0,0,0,0%); selection-color:black; selection-background-color:gray; border-radius:8px; border:4px solid green;}");

    connect(ui->linkman_listWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(listWidget_item_click()));


    initlistWidget();

    timer = new QTimer(this);
    uptimer = new QTimer(this);
    dtimer = new QTimer(this);
    itimer = new QTimer(this);
    //lcdNumber = new QLCDNumber;
    //timeEdit = new QTimeEdit;
    ui->lcdNumber->setNumDigits(8);						//��ʾ�˸����֣�Ĭ������ʾ5������
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);	//�����ɫ��Ĭ���ǰ�ɫ��
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));	//���ø�ʽ������������ʽ��

    ui->timeEdit->setDisplayFormat("hh:mm:ss");




    QIcon titleicon(":/images/origami-colored-pencil-03.png");
    trayIcon=new QSystemTrayIcon(titleicon,this);						//����icon
    trayIconMenu=new QMenu;
    showAct=new QAction(tr("show"),this);
    quitAct=new QAction(tr("quit"),this);


    trayIconMenu->addAction(showAct);
    trayIconMenu->addAction(quitAct);

    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    rect=QApplication::desktop()->rect();
    x=rect.right()-width()-438;
    y=rect.bottom();
    setGeometry(x,y,width(),height());



    connect(timer,SIGNAL(timeout()),this,SLOT(clockChange()));
    timer->start(1000);//ʱ������Ϊ��λ�ı�

    connect(uptimer,SIGNAL(timeout()),this,SLOT(dialogUp()));
    uptimer->start(20);

    connect(ui->timeSet_pushButton,SIGNAL(clicked()),dtimer,SIGNAL(timeout()));//

    connect(ui->mini_pushButton,SIGNAL(clicked()),this,SLOT(down()));

    connect(showAct,SIGNAL(triggered(bool)),uptimer,SIGNAL(timeout()));

    connect(itimer,SIGNAL(timeout()),this,SLOT(comToCur()));
    itimer->start(20);

    connect(this,SIGNAL(isCurrentTime()),uptimer,SIGNAL(timeout()));

    connect(itimer,SIGNAL(timeout()),this,SLOT(comToCur()));
    itimer->start(10);

    connect(dtimer,SIGNAL(timeout()),this,SLOT(down()));
    dtimer->start(20);//

    connect(quitAct,SIGNAL(triggered()),this,SLOT(close()));

}

void Dialog::clockChange()
{
    ui->lcdNumber->display(QTime::currentTime().toString("hh:mm:ss"));
}


void Dialog::comToCur()
{
    if( QVariant(QTime::currentTime()).toString() == QVariant(ui->timeEdit->time()).toString() )
    {
        QApplication::beep();
        emit isCurrentTime();
    }
}


void Dialog::dialogUp()
{
    qDebug()<<"time out!";
    //show();
    uptimer->start(20);
    if(y>=rect.bottom()-height()-226)
    {
        y-=5;
    }
    else
    {
        uptimer->stop();
    }
    setGeometry(x,y,width(),height());

}


void Dialog::down()
{
    dtimer->start(20);
    if(y<rect.bottom())
    {
        y+=height()+10;
    }
    else
    {
        dtimer->stop();
    }
    setGeometry(x,y,width(),height());
}


/*void Dialog::mini()
{
    hide();
    if(!this->isHidden())
    this->hide();
    else
        this->show();
}*/




Dialog::~Dialog()
{
    delete ui;
}


void Dialog::initlistWidget()
{
 ui->linkman_listWidget->clear();
 model=new QSqlQueryModel();
 model->setQuery("select * from AddBook");
 int rowNum = model->rowCount();
 for(int i = 0; i < rowNum; i++)
 {
    ui->linkman_listWidget->addItem(tr("name:  ")+model->record(i).value("name").toString()+".\t\v"+tr("number:  ")+model->record(i).value("number").toString());
 }
}


void Dialog::on_insert_pushButton_clicked()
{
    QSqlQuery query;
    if(ui->name_lineEdit->text().isEmpty()||ui->number_lineEdit->text().isEmpty())
    {
      qmessage_Dialog *a = new qmessage_Dialog(0,tr("��Ϣ����Ϊ�գ�"));
      a->setWindowFlags(Qt::FramelessWindowHint);
      a->exec();
    }
    else
    {
      QString name = ui->name_lineEdit->text();
      QString number = ui->number_lineEdit->text();
      QString sql ="";
      sql +="select * from AddBook where name like '";
      sql +=name+"'";
      query.exec(sql);
      if(query.next())
      {
        //����������ϵ���Ѵ��ڡ���ʾ��
        qmessage_Dialog *a = new qmessage_Dialog(0,tr("����ϵ���Ѵ��ڣ�"));
        a->setWindowFlags(Qt::FramelessWindowHint);
        a->exec();
      }
      else
      {
        sql ="insert into AddBook values('"+name+"'"+",";
        sql +=number+")";
        qDebug()<<sql;
        query.exec(sql);
        qmessage_Dialog *a = new qmessage_Dialog(0,tr("��ӳɹ���"));
        a->setWindowFlags(Qt::FramelessWindowHint);
        a->exec();
        delete model;
        initlistWidget();
      }
    }

}


void Dialog::on_delete_pushButton_clicked()
{
    int index = ui->linkman_listWidget->currentIndex().row();
    if(-1 == index)
    {
      //������δѡ�С���ʾ��
      qmessage_Dialog *a = new qmessage_Dialog(0,tr("δѡ�У�"));
      a->setWindowFlags(Qt::FramelessWindowHint);
      a->exec();
    }
    else
    {
      //������yes/no����ʾ��
      //yes������ȷ������ʾ��
      //noȡ��
      qmessage2_Dialog *dlg = new qmessage2_Dialog(0, tr("ȷ��ɾ����"));
      dlg->setWindowFlags(Qt::FramelessWindowHint);
      connect(dlg, SIGNAL(sendsignal(bool)), this, SLOT(receivesig(bool)));
      dlg->exec();
    }
}


void Dialog::receivesig(bool a)
{
    QSqlQuery query;
    if(1 == a)
    {
      QString number = ui->number2_lineEdit->text();
      QString sql ="delete from AddBook where number =";
      sql +=number;
      qDebug()<<sql;
      query.exec(sql);
      delete model;
      initlistWidget();
    }
}


void Dialog::on_modify_pushButton_clicked()
{
    int index = ui->linkman_listWidget->currentIndex().row();
    if(-1 == index)
    {
       //������δѡ�С���ʾ��
      qmessage_Dialog *a = new qmessage_Dialog(0,tr("δѡ�У�"));
      a->setWindowFlags(Qt::FramelessWindowHint);
      a->exec();
    }
    else
    {
        qmessage3_Dialog *dlg3 = new qmessage3_Dialog(0, tr("�޸�name����number��"));
        dlg3->setWindowFlags(Qt::FramelessWindowHint);
        connect(dlg3, SIGNAL(sendsignal(bool)), this, SLOT(receivesig_1(bool)));
        dlg3->exec();
    }
        /*ui->name2_lineEdit->del();
        ui->number2_lineEdit->del();
        query.exec(sql);
        if(query.next())
        {
            sql ="update student set name=";
            sql+="'"+name+"'";
            sql+="where num="+num;
            qDebug()<<sql;
            query.exec(sql);
        }
        else
        {
            QMessageBox::information(this,tr("��Ϣ"),tr("��ѧ�Ų�����"),QMessageBox::Yes);
        }*/
}


void Dialog::receivesig_1(bool a)
{
   //QSqlQuery query;
   if(1 == a)
   {
       QString number = ui->number2_lineEdit->text();
       modifymessage_Dialog *dlg = new modifymessage_Dialog(0, "number", "name", number);
       dlg->setWindowFlags(Qt::FramelessWindowHint);
       dlg->exec();
       delete model;
       initlistWidget();
   }
   else
   {
       QString name = ui->name2_lineEdit->text();
       modifymessage_Dialog *dlg = new modifymessage_Dialog(0, "name", "number", name);
       dlg->setWindowFlags(Qt::FramelessWindowHint);
       dlg->exec();
       delete model;
       initlistWidget();
   }
}


void Dialog::on_select_pushButton_clicked()
{
   QSqlQuery query;
   if(ui->name2_lineEdit->text().isEmpty())
   {
     qmessage_Dialog *a = new qmessage_Dialog(0,tr("��������Ϊ�գ�"));
     a->setWindowFlags(Qt::FramelessWindowHint);
     a->exec();
   }
   else
   {
   QString name = ui->name2_lineEdit->text();
   QString sql="";
   sql +="select * from AddBook where name like '%";
   sql +=name+"%'";
   qDebug()<<sql;
   query.exec(sql);
   if(query.next())
   {
      ui->name2_lineEdit->setText(query.value(0).toString());
      ui->number2_lineEdit->setText(query.value(1).toString());
   }
   else
    {
      //������û�д�����Ϣ����ʾ��
      qmessage_Dialog *a = new qmessage_Dialog(0,tr("û�д���ϵ����Ϣ��"));
      a->setWindowFlags(Qt::FramelessWindowHint);
      a->exec();
    }
   }
}


void Dialog::listWidget_item_click()
{
    int curRow=ui->linkman_listWidget->currentIndex().row();
    //int curCol=ui->linkman_tableView->currentIndex().column();
    //model->ditem(row, column)->text();
    ui->name2_lineEdit->setText(model->record(curRow).value("name").toString());
    ui->number2_lineEdit->setText(model->record(curRow).value("number").toString());

    /*if(curCol == 0)
    {
     ui->name2_lineEdit->setText(model->data(model->index(curRow,curCol)).toString());
     ui->number2_lineEdit->setText(model->data(model->index(curRow,curCol+1)).toString());
    }
    else
    {
     ui->name2_lineEdit->setText(model->data(model->index(curRow,curCol-1)).toString());
     ui->number2_lineEdit->setText(model->data(model->index(curRow,curCol)).toString());
    }*/
}



void Dialog::on_quit_pushButton_clicked()
{
   this->close();
}
