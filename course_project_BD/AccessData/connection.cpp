#include "connection.h"
#include "AccessDataConfiguration/accessdataconfiguration.h"
#include "AccessDataConfiguration/importinfoconnection.h"

#include <QDebug>
#include <QSqlError>

#include "loggingcategories.h"

Connection::Connection()
{
    AccessDataConfiguration config;
    ImportInfoConnection *info = config.getConfiguration();
    db = QSqlDatabase::addDatabase(info->getTypeDatabase());
    db.setHostName(info->getHostName());
    db.setDatabaseName(info->getDatabaseName());
    db.setUserName(info->getUserName());
    db.setPassword(info->getPassword());
    db.setPort(info->getPort().toInt());

    typeDB = info->getTypeDatabase();

    reconnect();
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

QSqlDatabase* Connection::getConnection()
{
    QSqlDatabase* res = &db;
    try
    {
        if (!db.isOpen())
            reconnect();

        if (!db.isOpen())
            throw -1;
    }
    catch (...)
    {
        qDebug(logCritical()) << "Unable to connect to DB" << __FILE__ << "Line: " << __LINE__ << endl;
        res = nullptr;
    }

    return res;
}

QString Connection::getTypeDB()
{
    return typeDB;
}

bool Connection::transaction()
{
    return db.transaction();
}

bool Connection::commit()
{
    return db.commit();
}

bool Connection::rollback()
{
    return db.rollback();
}

bool Connection::reconnect(int triesToConnect)
{
    bool isSuccess = true;
    try
    {
        db.open();
        if (!db.isOpen())
            throw -1;
        qDebug(logInfo()) << "Connection is open";
    }
    catch (...)
    {
        qDebug(logCritical()) << "Trying to connect to DB..." << db.lastError() << "Num try: " << triesToConnect
                              << __FILE__ << "Line: " << __LINE__ << endl;
        isSuccess = false;
    }

    return (triesToConnect++ < NUM_TRIES_TO_CONNECT && !isSuccess) ? reconnect(triesToConnect) : isSuccess;
}
