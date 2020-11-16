#ifndef ACCESSTODB_H
#define ACCESSTODB_H

#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>

class AccessToDB
{

public:
    AccessToDB();

    // work with Model
    QSqlQueryModel* getData(QSqlQuery &query);
    void select(QSqlRelationalTableModel *model);
    bool setData(QSqlRelationalTableModel &model);
    void run(QSqlQuery &query);

    int insert(QSqlQuery &query);
    int update(QSqlQuery &query);

private:
    bool checkValidTableName(const QString &tableName);
};

#endif // ACCESSTODB_H
