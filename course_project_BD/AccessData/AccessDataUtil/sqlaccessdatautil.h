#ifndef SQLACCESSDATAUTIL_H
#define SQLACCESSDATAUTIL_H


#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

#include "iaccessdatautil.h"
#include "AccessData/connection.h"
#include "AccessData/accesstodb.h"

#include "MyClasses/myqsqlquerymodel.h"

class SqlAccessDataUtil : IAccessDataUtil
{
    Connection *connection;
    AccessToDB access;
    bool needToColorOldDocs;

public:
    SqlAccessDataUtil();
    ~SqlAccessDataUtil() override;

    // work with Model
    QSqlQueryModel* getData(QString &queryString) override;
    QSqlRelationalTableModel* select(QString &tableName) override;
    bool setData(QSqlRelationalTableModel &model) override;
    MyQSqlQueryModel* run(const QString &sqlString) override;

    int insert(const QString &tableName, const QStringList &atributesName, const QStringList &atributesValue) override;
    int update(const QString &tableName, int idUpdate, const QStringList &atributesName,
               const QStringList &atributesValue) override;

    QStringList getSamePeople(QString tableName, int idPersonNotInclude, QString sameColumnName, QString sameColumnValue);

    bool transaction();
    bool commit();
    bool rollback();
    void setFlagNeedToColorOldDocs(bool flag);

private:
    bool checkValidTableName(const QString &tableName);

};

#endif // SQLACCESSDATAUTIL_H
