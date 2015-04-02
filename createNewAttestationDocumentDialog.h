#ifndef CREATENEWATTESTATIONDOCUMENTDIALOG_H
#define CREATENEWATTESTATIONDOCUMENTDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>
#include <QPrinter>
#include <QPrintDialog>
#include "myTableWidget.h"
#include "OneLineTextEdit.h"
#include "machinesManagingDialog.h"
#include "detailManagingDialog.h"

namespace Ui {
class createNewAttestationDocumentDialog;
}

class createNewAttestationDocumentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createNewAttestationDocumentDialog(QWidget *parent = 0);
    ~createNewAttestationDocumentDialog();

private slots:
    void m_focusChanged(QWidget *last, QWidget *current);
    void m_printerWasSelected(QPrinter *printer);

    void on_checkBox_1factParam_clicked(bool checked);
    void on_checkBox_2factParam_clicked(bool checked);
    void on_checkBox_3factParam_clicked(bool checked);

    void on_checkBox_1controlledParam_clicked(bool checked);
    void on_checkBox_2controlledParam_clicked(bool checked);
    void on_checkBox_3controlledParam_clicked(bool checked);

    void on_toolButton_clear1factParam_clicked();
    void on_toolButton_clear2factParam_clicked();
    void on_toolButton_clear3factParam_clicked();

    void on_toolButton_clear1controlledParam_clicked();
    void on_toolButton_clear2controlledParam_clicked();
    void on_toolButton_clear3controlledParam_clicked();


    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();

    void on_toolButton_degreeSymbol_clicked();
    void on_toolButton_multiplicationSymbol_clicked();
    void on_toolButton_plusMinusSymbol_clicked();
    void on_toolButton_diameterSymbol_clicked();
    void on_toolButton_lowerIndex_clicked();
    void on_toolButton_upperIndex_clicked();

    void m_slotChooseMachine();
    void m_slotChooseDetail();
    void m_slotChooseComission();
    void m_slotNewMachine(const bool isOk, const int number, const QString inventoryNumber, const QString type, const QString operationName, const QString model, const int group);
    void m_slotNewDetail(const bool isOk, const QString detailDesignation, const QString detailName);

private:
    Ui::createNewAttestationDocumentDialog *ui;

    machinesManagingDialog *m_machinesDialog;
    detailManagingDialog *m_detailsDialog;

    OneLineTextEdit *m_lastActiveLineEdit;
    bool m_lastActiveWidgetIsLineEdit;
    bool m_isLineEdit(const QWidget *widget);

    QPrintDialog *m_printDialog;
    QString m_documentPattern;
    QString m_document;


};

#endif // CREATENEWATTESTATIONDOCUMENTDIALOG_H
