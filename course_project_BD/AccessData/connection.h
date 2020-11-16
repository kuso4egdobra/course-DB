#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

#define NUM_TRIES_TO_CONNECT 20

class Connection
{
    QSqlDatabase db;
    QString typeDB;

public:
    Connection();
    ~Connection();
    QSqlDatabase* getConnection();
    QString getTypeDB();

    bool transaction();
    bool commit();
    bool rollback();

private:
    bool reconnect(int triesToConnect = 0);
};

#endif // CONNECTION_H
