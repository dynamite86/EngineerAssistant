#ifndef CREATENEWCARDOFHARMONIZATIONDIALOG_H
#define CREATENEWCARDOFHARMONIZATIONDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>

namespace Ui {
class createNewCardOfHarmonizationDialog;
}

class createNewCardOfHarmonizationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createNewCardOfHarmonizationDialog(QWidget *parent = 0);
    ~createNewCardOfHarmonizationDialog();


private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();

    void on_radioButton_createNewDocument_clicked(bool checked);

    void on_radioButton_importExistingDocument_clicked(bool checked);

private:
    Ui::createNewCardOfHarmonizationDialog *ui;
};

#endif // CREATENEWCARDOFHARMONIZATIONDIALOG_H
