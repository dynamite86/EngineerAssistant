#ifndef MACHINEEDITDIALOG_H
#define MACHINEEDITDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>

namespace Ui {
class machineEditDialog;
}

enum MachineWorkingResume{
    newMachine,
    existingMachine
};

class machineEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit machineEditDialog(QWidget *parent = 0);
    ~machineEditDialog();


    bool initEditor(const MachineWorkingResume workingResume = newMachine, const int numberInPlan = -1, const QString inventoryNumber = QString(), const QString type = QString(), const QString operationName = QString(), const QString model = QString(), const int group = -1);

private:
    Ui::machineEditDialog *ui;
    uchar m_workingResume;

    int m_numberInPlan;
    QString m_inventoryNumber;
    QString m_type;
    QString m_operationName;
    QString m_model;
    int m_group;

signals:
    void m_signalNewMachine(const bool isOk = false, const MachineWorkingResume workingResume = newMachine, const int numberInPlan = -1, const QString inventoryNumber = QString(), const QString type = QString(), const QString operationName = QString(), const QString model = QString(), const int group = -1);

private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // MACHINEEDITDIALOG_H
