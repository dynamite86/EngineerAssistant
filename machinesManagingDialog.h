#ifndef MACHINESMANAGINGDIALOG_H
#define MACHINESMANAGINGDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>
#include "myTableWidget.h"
#include "machineEditDialog.h"

namespace Ui {
class machinesManagingDialog;
}

class machinesManagingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit machinesManagingDialog(QWidget *parent = 0);
    ~machinesManagingDialog();

private:
    Ui::machinesManagingDialog *ui;
    machineEditDialog *m_machineEdit;
    int m_lastRow;

signals:
    void m_signalNewMachine(const bool isOk = false, const int numberInPlan = -1, const QString inventoryNumber = QString(), const QString type = QString(), const QString operationName = QString(), const QString model = QString(), const int group = -1);

private slots:
    void m_slotNewMachine(const bool isOk, const MachineWorkingResume workingResume, const int numberInPlan, const QString inventoryNumber, const QString type, const QString operationName, const QString model, const int group);
    void on_pushButton_done_clicked();
    void on_pushButton_aom_newRecord_clicked();
    void on_pushButton_aom_editRecord_clicked();
    void on_pushButton_aom_deleteRecord_clicked();
};

#endif // MACHINESMANAGINGDIALOG_H
