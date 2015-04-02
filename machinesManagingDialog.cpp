#include "machinesManagingDialog.h"
#include "ui_machinesManagingDialog.h"

machinesManagingDialog::machinesManagingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::machinesManagingDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    ui->tableWidget_aom_machinesTable->setRowsAutoResize(true);
    ui->tableWidget_aom_machinesTable->setColumnsAutoResize(true);
    m_machineEdit = new machineEditDialog(this);
    connect(m_machineEdit, SIGNAL(m_signalNewMachine(bool,MachineWorkingResume,int,QString,QString,QString,QString,int)), this, SLOT(m_slotNewMachine(bool,MachineWorkingResume,int,QString,QString,QString,QString,int)));
}

machinesManagingDialog::~machinesManagingDialog()
{
    delete m_machineEdit;
    delete ui;
}

void machinesManagingDialog::on_pushButton_done_clicked()
{
    QString inventoryNumber;
    QString type;
    QString operationName;
    QString model;
    int group  = 0;
    int number = 0;
    bool isOk  = false;

    QList<QTableWidgetItem*> items = ui->tableWidget_aom_machinesTable->selectedItems();
    if(items.isEmpty())
    {
        m_signalNewMachine();
        this->reject();
    }

    //номер по графику
    if(items.at(0))
    {
        number = items.at(0)->text().toInt(&isOk, 10);
        if(!isOk)
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }

    //инвентарный номер
    if(items.at(1))
    {
        inventoryNumber = items.at(1)->text();
        if(inventoryNumber.isEmpty())
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }

    //тип станка
    if(items.at(2))
    {
        type = items.at(2)->text();
        if(type.isEmpty())
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }

    //наименование операции
    if(items.at(3))
    {
        operationName = items.at(3)->text();
        if(operationName.isEmpty())
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }


    //модель станка
    if(items.at(4))
    {
        model = items.at(4)->text();
        if(model.isEmpty())
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }

    //участок
    if(items.at(5))
    {
        group = items.at(5)->text().toInt(&isOk, 10);
        if(!isOk)
        {
            m_signalNewMachine();
            this->reject();
        }
    }
    else
    {
        m_signalNewMachine();
        this->reject();
    }

    m_signalNewMachine(true, number, inventoryNumber, type, operationName, model, group);
    this->accept();
}

void machinesManagingDialog::on_pushButton_aom_newRecord_clicked()
{
    m_machineEdit->initEditor();
    m_machineEdit->exec();
}

void machinesManagingDialog::m_slotNewMachine(const bool isOk, const MachineWorkingResume workingResume, const int numberInPlan, const QString inventoryNumber, const QString type, const QString operationName, const QString model, const int group)
{
    QStringList newItems;
    if(isOk)
    {
        switch(workingResume)
        {
            case newMachine:
                {
                    newItems = QStringList() << QString::number(numberInPlan)
                                             << inventoryNumber
                                             << type
                                             << operationName
                                             << model
                                             << QString::number(group);

                    ui->tableWidget_aom_machinesTable->appendRow(newItems);
                }
                break;

            case existingMachine:
                {
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 0, numberInPlan);
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 1, inventoryNumber);
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 2, type);
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 3, operationName);
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 4, model);
                    ui->tableWidget_aom_machinesTable->setCellContent(m_lastRow, 5, group);
                }
                break;
        }
    }
}

void machinesManagingDialog::on_pushButton_aom_editRecord_clicked()
{
    QString inventoryNumber;
    QString type;
    QString operationName;
    QString model;
    int group  = 0;
    int number = 0;
    bool isOk  = false;

    QList<QTableWidgetItem*> items = ui->tableWidget_aom_machinesTable->selectedItems();
    if(items.isEmpty())
    {
        return;
    }

    //номер по графику
    if(items.at(0))
    {
        m_lastRow = items.at(0)->row();
        if(m_lastRow == -1)
        {
            return;
        }

        number = items.at(0)->text().toInt(&isOk, 10);
        if(!isOk)
        {
            return;
        }
    }
    else
    {
        return;
    }

    //инвентарный номер
    if(items.at(1))
    {
        inventoryNumber = items.at(1)->text();
        if(inventoryNumber.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }

    //тип станка
    if(items.at(2))
    {
        type = items.at(2)->text();
        if(type.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }

    //наименование операции
    if(items.at(3))
    {
        operationName = items.at(3)->text();
        if(operationName.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }


    //модель станка
    if(items.at(4))
    {
        model = items.at(4)->text();
        if(model.isEmpty())
        {
            return;
        }
    }
    else
    {
        return;
    }

    //участок
    if(items.at(5))
    {
        group = items.at(5)->text().toInt(&isOk, 10);
        if(!isOk)
        {
            return;
        }
    }
    else
    {
        return;
    }

    m_machineEdit->initEditor(existingMachine, number, inventoryNumber, type, operationName, model, group);
    m_machineEdit->exec();
}

void machinesManagingDialog::on_pushButton_aom_deleteRecord_clicked()
{
    bool isOk = false;
    int row   = 0;
    if(!ui->tableWidget_aom_machinesTable->selectedItems().isEmpty())
    {
        row = ui->tableWidget_aom_machinesTable->selectedItems().first()->row();
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
            ui->tableWidget_aom_machinesTable->deleteRow(row);
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
