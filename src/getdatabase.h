#ifndef GETDATABASE_H
#define GETDATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QMessageBox>

class getDataBase
{
public:
    getDataBase();
    bool createConnection(QString daname);
    void createTables();
    void createDatabase();
private:
    QSqlDatabase db;
};

#endif // GETDATABASE_H
