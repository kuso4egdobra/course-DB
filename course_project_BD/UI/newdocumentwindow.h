#ifndef NEWDOCUMENTWINDOW_H
#define NEWDOCUMENTWINDOW_H

#include <QWidget>
#include <QTableWidget>

#include "BusinessLogic/DataToBusiness/datafromguitobusiness.h"

namespace Ui {
class NewDocumentWindow;
}

class NewDocumentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewDocumentWindow(DataFromGuiToBusiness *sender, QWidget *parent = nullptr);
    ~NewDocumentWindow();

private:
    Ui::NewDocumentWindow *ui;
    DataFromGuiToBusiness *sender;
    void hideDocs();
    void checkUI();

signals:
    void openWindow();

private slots:
    void on_BtnReset_clicked();
    void on_checkBox_otherDoc_stateChanged(int checked);
    void on_btn_addOtherAtribute_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_BtnOk_clicked();
    void on_checkBox_personInDB_stateChanged(int arg1);
    void on_combo_typeDoc_currentIndexChanged(int index);
    void on_checkBox_noendDoc_stateChanged(int arg1);
};

#endif // NEWDOCUMENTWINDOW_H
