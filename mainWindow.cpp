#include "mainWindow.h"
#include "ui_mainWindow.h"

void mainWindow::m_initControls()
{
    ui->tableWidget_aom_machinesTable->setRowsAutoResize(true);
    ui->tableWidget_aom_machinesTable->setColumnsAutoResize(true);
    ui->tableWidget_coh_cardsOfHarmonizationTable->setRowsAutoResize(true);
    ui->tableWidget_coh_cardsOfHarmonizationTable->setColumnsAutoResize(true);
    ui->toolBox->setCurrentIndex(0);
}

void mainWindow::m_initStatusBar()
{
    m_workshop        = new QLabel(ui->statusBar);
    m_userName        = new QLabel(ui->statusBar);
    m_userGroup       = new QLabel(ui->statusBar);
    m_connectionState = new QLabel(ui->statusBar);

    ui->statusBar->addPermanentWidget(m_workshop,        1);
    ui->statusBar->addPermanentWidget(m_userName,        1);
    ui->statusBar->addPermanentWidget(m_userGroup,        1);
    ui->statusBar->addPermanentWidget(m_connectionState, 1);

    m_workshop->setText("Цех: <b>8</b>");
    m_userName->setText("Пользователь: <b>Мельничук Евгений Валерьевич</b>");
    m_userGroup->setText("Группа: <b>администраторы</b>");
    m_connectionState->setText("Соединение с сервером: <b>установлено</b>");
}

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    m_initControls();
    m_initStatusBar();
}

mainWindow::~mainWindow()
{
    delete m_connectionState;
    delete m_userGroup;
    delete m_userName;
    delete m_workshop;
    delete ui;
}

void mainWindow::on_action_attestationOfMachines_triggered()
{
    ui->toolBox->setCurrentIndex(0);
}
void mainWindow::on_action_soglasovaniya_triggered()
{
    ui->toolBox->setCurrentIndex(1);
}

void mainWindow::on_pushButton_aom_newRecord_clicked()
{
    AttestationDocumentDialog createAttestationDocument(this);
    createAttestationDocument.exec();
}

void mainWindow::on_action_exit_triggered()
{
    this->close();
}

void mainWindow::closeEvent(QCloseEvent *event)
{
    int result = QMessageBox::question(this, this->windowTitle(), "Вы действительно хотите выйти из программы?", QMessageBox::Yes|QMessageBox::No);
    if(QMessageBox::Yes == result){
        event->accept();
    }else{
        event->ignore();
    }
}

void mainWindow::on_action_aboutQt_triggered()
{
    QApplication::aboutQt();
}

void mainWindow::on_action_about_triggered()
{
    aboutDialog about(this);
    about.exec();
}

void mainWindow::on_pushButton_coh_newRecord_clicked()
{
    createNewCardOfHarmonizationDialog createNewCardOfHarmonization(this);
    createNewCardOfHarmonization.exec();
}

void mainWindow::on_pushButton_aom_deleteRecord_clicked()
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

void mainWindow::on_pushButton_coh_deleteRecord_clicked()
{
    bool isOk = false;
    int row   = 0;
    if(!ui->tableWidget_coh_cardsOfHarmonizationTable->selectedItems().isEmpty())
    {
        row = ui->tableWidget_coh_cardsOfHarmonizationTable->selectedItems().first()->row();
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
            ui->tableWidget_coh_cardsOfHarmonizationTable->deleteRow(row);
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

void mainWindow::on_pushButton_aom_viewDocument_clicked()
{

}
