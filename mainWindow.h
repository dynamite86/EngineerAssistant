#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>
#include <QStyleFactory>
#include "myTableWidget.h"
#include "createNewAttestationDocumentDialog.h"
#include "createNewCardOfHarmonizationDialog.h"
#include "aboutDialog.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

private slots:
    void on_action_attestationOfMachines_triggered();
    void on_action_exit_triggered();
    void closeEvent(QCloseEvent *event);

    void on_pushButton_aom_newRecord_clicked();
    void on_pushButton_coh_newRecord_clicked();
    void on_action_soglasovaniya_triggered();
    void on_action_aboutQt_triggered();
    void on_action_about_triggered();

    void on_pushButton_aom_deleteRecord_clicked();

    void on_pushButton_coh_deleteRecord_clicked();

    void on_pushButton_aom_viewDocument_clicked();

private:
    Ui::mainWindow *ui;
    QLabel         *pWorkshop;
    QLabel         *pUserName;
    QLabel         *pConnectionState;

    void pInitControls();
    void pInitStatusBar();
};

#endif // MAINWINDOW_H
