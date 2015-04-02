#include "detailEditDialog.h"
#include "ui_detailEditDialog.h"

detailEditDialog::detailEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::detailEditDialog)
{
    ui->setupUi(this);
}

detailEditDialog::~detailEditDialog()
{
    delete ui;
}

bool detailEditDialog::initEditor(const DetailWorkingResume workingResume, const QString detailDesignation, const QString detailName)
{
    m_workingResume = workingResume;

    switch(workingResume)
    {
        case newDetail:
            {
                this->setWindowTitle("Добавление новой детали");
                ui->lineEdit_detailDesignation->clear();
                ui->lineEdit_detailName->clear();
            }
            break;

        case existingDetail:
            {
                this->setWindowTitle("Редактирование детали");
                if(detailDesignation.isEmpty()||detailName.isEmpty())
                {
                    return false;
                }
                else
                {
                    ui->lineEdit_detailDesignation->setText(detailDesignation);
                    ui->lineEdit_detailName->setText(detailName);
                }
            }
            break;

        default:
            {
                return false;
            }
    }

    return true;
}

void detailEditDialog::on_pushButton_save_clicked()
{

    if(ui->lineEdit_detailDesignation->text().isEmpty())
    {
        m_signalNewDetail();
        this->reject();
    }

    if(ui->lineEdit_detailName->text().isEmpty())
    {
        m_signalNewDetail();
        this->reject();
    }

    m_signalNewDetail(true, (DetailWorkingResume)m_workingResume, ui->lineEdit_detailDesignation->text(), ui->lineEdit_detailName->text());
    this->accept();
}

void detailEditDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}
