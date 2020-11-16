#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QDialog>

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"

namespace Ui {
class StatisticsWindow;
}

class StatisticsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StatisticsWindow(DataFromGuiToBusiness *sender, QWidget *parent = nullptr);
    ~StatisticsWindow();

signals:
    void openWindow();

private slots:
    void on_BtnReset_clicked();
    void on_Btn_importConfig_clicked();
    void on_BtnOk_clicked();

private:
    Ui::StatisticsWindow *ui;
    DataFromGuiToBusiness *sender;
    QSqlQueryModel *model;
    QString configFilePath;
};

#endif // STATISTICSWINDOW_H
