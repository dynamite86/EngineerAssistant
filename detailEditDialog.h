#ifndef DETAILEDITDIALOG_H
#define DETAILEDITDIALOG_H

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>

namespace Ui {
class detailEditDialog;
}

enum DetailWorkingResume{
    newDetail,
    existingDetail
};

class detailEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit detailEditDialog(QWidget *parent = 0);
    ~detailEditDialog();


    bool initEditor(const DetailWorkingResume workingResume = newDetail, const QString detailDesignation = QString(), const QString detailName = QString());

private:
    Ui::detailEditDialog *ui;
    uchar m_workingResume;

signals:
    void m_signalNewDetail(const bool isOk = false, const DetailWorkingResume workingResume = newDetail, const QString detailDesignation = QString(), const QString detailName = QString());

private slots:
    void on_pushButton_save_clicked();
    void on_pushButton_cancel_clicked();
};

#endif // DETAILEDITDIALOG_H
