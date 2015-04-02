#include "createNewCardOfHarmonizationDialog.h"
#include "ui_createNewCardOfHarmonizationDialog.h"

createNewCardOfHarmonizationDialog::createNewCardOfHarmonizationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createNewCardOfHarmonizationDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
}

createNewCardOfHarmonizationDialog::~createNewCardOfHarmonizationDialog()
{
    delete ui;
}

void createNewCardOfHarmonizationDialog::on_pushButton_save_clicked()
{
    this->accept();
}

void createNewCardOfHarmonizationDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}

void createNewCardOfHarmonizationDialog::on_radioButton_createNewDocument_clicked(bool checked)
{
    if(checked){
        ui->radioButton_importExistingDocument->setChecked(false);
        ui->pushButton_importFromFile->setDisabled(true);
        ui->pushButton_importFromScaner->setDisabled(true);
    }
}

void createNewCardOfHarmonizationDialog::on_radioButton_importExistingDocument_clicked(bool checked)
{
    if(checked){
        ui->radioButton_createNewDocument->setChecked(false);
        ui->pushButton_importFromFile->setEnabled(true);
        ui->pushButton_importFromScaner->setEnabled(true);
    }
}
