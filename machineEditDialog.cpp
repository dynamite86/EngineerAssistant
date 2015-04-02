#include "machineEditDialog.h"
#include "ui_machineEditDialog.h"

machineEditDialog::machineEditDialog(QWidget *parent) : QDialog(parent), ui(new Ui::machineEditDialog)
{
    ui->setupUi(this);
    ui->comboBox_type->setAutoCompletion(true);
    ui->comboBox_operationName->setAutoCompletion(true);
    ui->comboBox_group->setAutoCompletion(true);
}

machineEditDialog::~machineEditDialog()
{
    delete ui;
}

bool machineEditDialog::initEditor(const MachineWorkingResume workingResume, const int numberInPlan, const QString inventoryNumber, const QString type, const QString operationName, const QString model, const int group)
{
    m_workingResume = workingResume;

    switch(workingResume)
    {
        case newMachine:
            {
                this->setWindowTitle("Добавление нового станка");
                ui->spinBox_numberInPlan->setValue(0);
                ui->lineEdit_inventoryNumber->clear();
                ui->comboBox_type->setCurrentIndex(0);
                ui->comboBox_operationName->setCurrentIndex(0);
                ui->lineEdit_model->clear();
                ui->comboBox_group->setCurrentIndex(0);
            }
            break;

        case existingMachine:
            {
                this->setWindowTitle("Редактирование станка");
                if((inventoryNumber.isEmpty()|| type.isEmpty()||operationName.isEmpty()|| model.isEmpty()||(group  <= 0)||(numberInPlan <= 0)))
                {
                    return false;
                }
                else
                {
                    ui->spinBox_numberInPlan->setValue(numberInPlan);
                    ui->lineEdit_inventoryNumber->setText(inventoryNumber);
                    ui->lineEdit_model->setText(model);

                    qDebug() << "ui->comboBox_type->findText(type, Qt::MatchFixedString) = " << ui->comboBox_type->findText(type, Qt::MatchFixedString);
                    if(ui->comboBox_type->findText(type, Qt::MatchFixedString) == -1)
                    {
                        return false;
                    }
                    else
                    {
                        ui->comboBox_type->setCurrentIndex(ui->comboBox_type->findText(type, Qt::MatchFixedString));
                    }

                    qDebug() << "ui->comboBox_operationName->findText(operationName, Qt::MatchFixedString) = " << ui->comboBox_operationName->findText(operationName, Qt::MatchFixedString);
                    if(ui->comboBox_operationName->findText(operationName, Qt::MatchFixedString) == -1)
                    {
                        return false;
                    }
                    else
                    {
                        ui->comboBox_operationName->setCurrentIndex(ui->comboBox_operationName->findText(type, Qt::MatchFixedString));
                    }

                    qDebug() << "ui->comboBox_group->findText(QString::number(group), Qt::MatchFixedString) = " << ui->comboBox_group->findText(QString::number(group), Qt::MatchFixedString);
                    if(ui->comboBox_group->findText(QString::number(group), Qt::MatchFixedString) == -1)
                    {
                        return false;
                    }
                    else
                    {
                        ui->comboBox_group->setCurrentIndex(ui->comboBox_group->findText(type, Qt::MatchFixedString));
                    }
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

void machineEditDialog::on_pushButton_save_clicked()
{
    QString inventoryNumber;
    QString type;
    QString operationName;
    QString model;
    int group        = 0;
    int numberInPlan = 0;
    bool isOk        = false;

    //номер по графику
    if(ui->spinBox_numberInPlan->value() <= 0)
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        numberInPlan = ui->spinBox_numberInPlan->value();
    }

    //инвентарный номер
    if(ui->lineEdit_inventoryNumber->text().isEmpty())
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        inventoryNumber = ui->lineEdit_inventoryNumber->text();
    }

    //тип станка
    if(ui->comboBox_type->currentIndex() == -1)
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        type = ui->comboBox_type->currentText();
    }

    //наименование операции
    if(ui->comboBox_operationName->currentIndex() == -1)
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        operationName = ui->comboBox_operationName->currentText();
    }

    //модель станка
    if(ui->lineEdit_model->text().isEmpty())
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        model = ui->lineEdit_model->text();
    }

    //участок
    if(ui->comboBox_group->currentIndex() == -1)
    {
        m_signalNewMachine();
        this->reject();
    }
    else
    {
        group = ui->comboBox_group->currentText().toInt(&isOk, 10);
        if(!isOk)
        {
            m_signalNewMachine();
            this->reject();
        }
    }

    m_signalNewMachine(true, (MachineWorkingResume)m_workingResume, numberInPlan, inventoryNumber, type, operationName, model, group);
    this->accept();
}

void machineEditDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}
