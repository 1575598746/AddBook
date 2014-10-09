#include "src/getdatabase.h"

getDataBase::getDataBase()
{
}

bool getDataBase::createConnection(QString dbname)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
    if(!db.open())
    {
     QMessageBox::critical(0,"cannot open database","Unabel to connect",QMessageBox::Cancel);
     return false;
    }
    return true;
}

void getDataBase::createTables()
{

}

void getDataBase::createDatabase()
{

}

