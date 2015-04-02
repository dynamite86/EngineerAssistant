#include "detailManagingDialog.h"
#include "ui_detailManagingDialog.h"

detailManagingDialog::detailManagingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::detailManagingDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    ui->tableWidget_aom_detailsTable->setRowsAutoResize(true);
    ui->tableWidget_aom_detailsTable->setColumnsAutoResize(true);
    m_detailEdit = new detailEditDialog(this);
    connect(m_detailEdit, SIGNAL(m_signalNewDetail(bool,DetailWorkingResume,QString,QString)), this, SLOT(m_slotNewDetail(bool,DetailWorkingResume,QString,QString)));
}

detailManagingDialog::~detailManagingDialog()
{
    delete ui;
}

void detailManagingDialog::on_pushButton_done_clicked()
{
    QString detailDesignation;
    QString detailName;

    QList<QTableWidgetItem*> items = ui->tableWidget_aom_detailsTable->selectedItems();
    if(items.isEmpty())
    {
        m_signalNewDetail();
        this->reject();
    }

    if(items.at(0))
    {
        detailDesignation = items.at(0)->text();
        if(detailDesignation.isEmpty())
        {
            m_signalNewDetail();
            this->reject();
        }
    }

    if(items.at(1))
    {
        detailName = items.at(0)->text();
        if(detailName.isEmpty())
        {
            m_signalNewDetail();
            this->reject();
        }
    }

    m_signalNewDetail(true, detailDesignation, detailName);
    this->accept();
}

void detailManagingDialog::on_pushButton_aom_newRecord_clicked()
{
    m_detailEdit->initEditor();
    m_detailEdit->exec();
}

void detailManagingDialog::m_slotNewDetail(const bool isOk, const DetailWorkingResume workingResume, const QString detailDesignation, const QString detailName)
{
    QStringList newItems;
    if(isOk)
    {
        switch(workingResume)
        {
            case newDetail:
                {
                    newItems = QStringList() << detailDesignation << detailName;

                    ui->tableWidget_aom_detailsTable->appendRow(newItems);
                }
                break;

            case existingDetail:
                {
                    ui->tableWidget_aom_detailsTable->setCellContent(m_lastRow, 0, detailDesignation);
                    ui->tableWidget_aom_detailsTable->setCellContent(m_lastRow, 1, detailName);
                }
                break;
        }
    }
}

void detailManagingDialog::on_pushButton_aom_editRecord_clicked()
{
    QString detailDesignation;
    QString detailName;

    QList<QTableWidgetItem*> items = ui->tableWidget_aom_detailsTable->selectedItems();
    if(items.isEmpty())
    {
        return;
    }

    if(items.at(0))
    {
        m_lastRow = items.at(0)->row();
        if(m_lastRow == -1)
        {
            return;
        }

        detailDesignation = items.at(0)->text();
        if(detailDesignation.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }

    if(items.at(1))
    {
        detailName = items.at(1)->text();
        if(detailName.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }

    m_detailEdit->initEditor(existingDetail, detailDesignation, detailName);
    m_detailEdit->exec();
}

void detailManagingDialog::on_pushButton_aom_deleteRecord_clicked()
{
    bool isOk = false;
    int row   = 0;
    if(!ui->tableWidget_aom_detailsTable->selectedItems().isEmpty())
    {
        row = ui->tableWidget_aom_detailsTable->selectedItems().first()->row();
        if(row == -1)
        {
            return;
        }
    }
    else
    {
        return;
    }

    QString password = QInputDialog::getText(this, "Подтверждение удаления записи", "Введите пароль", QLineEdit::Password, "", &isOk);
    if(isOk&&(!password.isEmpty()))
    {
        if(password.compare("qwerty", Qt::CaseInsensitive) == 0)
        {
            ui->tableWidget_aom_detailsTable->deleteRow(row);
        }
        else
        {
            QMessageBox::critical(this, this->windowTitle(), "Введенный пароль неверен! В доступе отказано!");
        }
    }
    else
    {
        QMessageBox::critical(this, this->windowTitle(), "Пароль не был введен! В доступе отказано!");
    }
}
