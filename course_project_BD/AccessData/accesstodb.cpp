#include "accesstodb.h"

#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>

#include "loggingcategories.h"

AccessToDB::AccessToDB()
{

}

QSqlQueryModel* AccessToDB::getData(QSqlQuery &query)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    try
    {
        run(query);
        model->setQuery(query);
    }
    catch (...)
    {
        qDebug(logCritical()) << query.lastError() << __FILE__ << "Line: " << __LINE__ << endl;
        delete model;
        model = nullptr;
    }

    return model;
}

void AccessToDB::select(QSqlRelationalTableModel *model)
{
    try
    {
        if (!model->select())
            throw -1;
    }
    catch (...)
    {
        qDebug(logCritical()) << model->lastError()  << __FILE__ << "Line: " << __LINE__ << endl;
        delete model;
        model = nullptr;
    }
}

bool AccessToDB::setData(QSqlRelationalTableModel &model)
{
    return model.submitAll();
}

void AccessToDB::run(QSqlQuery &query)
{
    try
    {
        if (!query.exec())
            throw -1;
    }
    catch(...)
    {
        qDebug(logCritical()) << query.lastError() << "\nFile: " << __FILE__ << "\nLine: " << __LINE__ << endl;
    }
}

int AccessToDB::insert(QSqlQuery &query)
{
    int res = 0;
    try
    {
        run(query);

        query.next();
        res = query.record().value(0).toInt();
    }
    catch (...)
    {
        qDebug(logCritical()) << query.lastError() << "\nFile: " << __FILE__ << "\nLine: " << __LINE__ << endl;
        res = -1;
    }

    return res;
}

int AccessToDB::update(QSqlQuery &query)
{
    int res = 0;
    try
    {
        run(query);
    }
    catch (...)
    {
        qDebug(logCritical()) << query.lastError() << __FILE__ << "Line: " << __LINE__ << endl;
        res = -1;
    }

    return res;
}
