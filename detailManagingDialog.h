#ifndef DETAILMANAGINGDIALOG_H
#define DETAILMANAGINGDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>
#include "myTableWidget.h"
#include "detailEditDialog.h"

namespace Ui {
class detailManagingDialog;
}

class detailManagingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit detailManagingDialog(QWidget *parent = 0);
    ~detailManagingDialog();


signals:
    void m_signalNewDetail(const bool isOk = false, const QString detailDesignation = QString(), const QString detailName = QString());

private slots:
    void m_slotNewDetail(const bool isOk, const DetailWorkingResume workingResume, const QString detailDesignation, const QString detailName);

    void on_pushButton_done_clicked();
    void on_pushButton_aom_newRecord_clicked();
    void on_pushButton_aom_editRecord_clicked();

    void on_pushButton_aom_deleteRecord_clicked();

private:
    Ui::detailManagingDialog *ui;
    detailEditDialog *m_detailEdit;
    int m_lastRow;
};

#endif // DETAILMANAGINGDIALOG_H
