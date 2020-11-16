#include "adminwindow.h"
#include "ui_adminwindow.h"

#include <QDebug>
#include <QSqlError>
#include <QMessageBox>

#include "LoggingCategories.h"

AdminWindow::AdminWindow(DataFromGuiToBusiness *sender, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    this->sender = sender;
    model = nullptr;
}

AdminWindow::~AdminWindow()
{
    delete ui;

    if (model)
        delete model;
}

void AdminWindow::on_BtnReset_clicked()
{
    qDebug(logInfo()) << "Выход из окна администрирования";
    this->close();
    emit openWindow();
}

void AdminWindow::on_BtnOk_clicked()
{
    if (model)
    {
        delete model;
        model = nullptr;
    }

    auto str = ui->textEdit_sqlEntry->toPlainText();
    qDebug(logInfo()) << "Отправка SQL запроса";
    model = sender->sendSqlQuery(str, true);

    if (model)
    {
        ui->tableView->setModel(model);
        QMessageBox::information(this, "", "Запрос успешно выполнен");
        qDebug(logInfo()) << "Запрос успешно выполнен";
    }
    else
    {
        QMessageBox::critical(this, "", "Ошибка выполнения запроса!");
        qDebug(logCritical()) << "Ошибка выполнения запроса!";
    }
}

void AdminWindow::on_checkBox_stateChanged(int checked)
{
    sender->setFlagNeedToColorOldDocs(checked);
}
