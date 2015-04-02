#include "createNewAttestationDocumentDialog.h"
#include "ui_createNewAttestationDocumentDialog.h"

createNewAttestationDocumentDialog::createNewAttestationDocumentDialog(QWidget *parent) : QDialog(parent), ui(new Ui::createNewAttestationDocumentDialog)
{
    ui->setupUi(this);

    ui->checkBox_1controlledParam->setChecked(true);
    ui->checkBox_2controlledParam->setChecked(true);
    ui->checkBox_3controlledParam->setChecked(false);

    ui->textEdit_1controlledParam->setEnabled(true);
    ui->textEdit_2controlledParam->setEnabled(true);
    ui->textEdit_3controlledParam->setEnabled(false);

    ui->checkBox_1factParam->setChecked(true);
    ui->checkBox_2factParam->setChecked(true);
    ui->checkBox_3factParam->setChecked(false);

    ui->textEdit_1factParam->setEnabled(true);
    ui->textEdit_2factParam->setEnabled(true);
    ui->textEdit_3factParam->setEnabled(false);
    this->setWindowFlags(Qt::Window);

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)), this, SLOT(m_focusChanged(QWidget*,QWidget*)));
    m_lastActiveWidgetIsLineEdit = false;

    QFile file(":/html/res/html/MachineAttestationDocumentPattern.html");
    file.open(QIODevice::ReadOnly);
    m_documentPattern = file.readAll();
    file.close();

    m_printDialog = new QPrintDialog(this);
    connect(m_printDialog, SIGNAL(accepted(QPrinter*)), this, SLOT(m_printerWasSelected(QPrinter*)));

    m_machinesDialog = new machinesManagingDialog(this);
    connect(m_machinesDialog, SIGNAL(m_signalNewMachine(bool,int,QString,QString,QString,QString,int)), this, SLOT(m_slotNewMachine(bool,int,QString,QString,QString,QString,int)));
    connect(ui->toolButton_numberInPlan,    SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));
    connect(ui->toolButton_inventoryNumber, SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));
    connect(ui->toolButton_type,            SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));
    connect(ui->toolButton_operationName,   SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));
    connect(ui->toolButton_model,           SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));
    connect(ui->toolButton_group,           SIGNAL(clicked()), this, SLOT(m_slotChooseMachine()));

    m_detailsDialog = new detailManagingDialog(this);
    connect(m_detailsDialog, SIGNAL(m_signalNewDetail(bool,QString,QString)), this, SLOT(m_slotNewDetail(bool,QString,QString)));
    connect(ui->toolButton_designation, SIGNAL(clicked()), this, SLOT(m_slotChooseDetail()));
    connect(ui->toolButton_detailName,  SIGNAL(clicked()), this, SLOT(m_slotChooseDetail()));
}

createNewAttestationDocumentDialog::~createNewAttestationDocumentDialog()
{
    delete m_detailsDialog;
    delete m_machinesDialog;
    delete m_printDialog;
    delete ui;
}

bool createNewAttestationDocumentDialog::m_isLineEdit(const QWidget *widget)
{
   return dynamic_cast<const OneLineTextEdit*>(widget) != 0;
}

void createNewAttestationDocumentDialog::m_focusChanged(QWidget *last, QWidget *current)
{
    if(m_isLineEdit(last)&&(last != current))
    {
        if(last->objectName().contains("Param"))
        {
            m_lastActiveWidgetIsLineEdit = true;
            m_lastActiveLineEdit = dynamic_cast<OneLineTextEdit*>(last);
            return;
        }
    }
    m_lastActiveWidgetIsLineEdit = false;
}

void createNewAttestationDocumentDialog::m_printerWasSelected(QPrinter *printer)
{
//    QTextDocument document;
    if(printer->isValid()){
//        printer->setCreator(this->parentWidget()->windowTitle());
//        printer->setDocName(this->windowTitle());
//        printer->setPrintProgram(this->windowTitle());
//        printer->setFullPage(true);
//        printer->setPaperSize(QPrinter::A4);
//        printer->setOrientation(QPrinter::Portrait);
//        printer->setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
//        document.setHtml(m_document);
//        document.print(printer);
    }
    this->accept();
}

void createNewAttestationDocumentDialog::on_checkBox_1factParam_clicked(bool checked)
{
    ui->checkBox_1controlledParam->setChecked(checked);
    ui->textEdit_1factParam->setEnabled(checked);
    ui->textEdit_1controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_checkBox_2factParam_clicked(bool checked)
{
    ui->checkBox_2controlledParam->setChecked(checked);
    ui->textEdit_2factParam->setEnabled(checked);
    ui->textEdit_2controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_checkBox_3factParam_clicked(bool checked)
{
    ui->checkBox_3controlledParam->setChecked(checked);
    ui->textEdit_3factParam->setEnabled(checked);
    ui->textEdit_3controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_checkBox_1controlledParam_clicked(bool checked)
{
    ui->checkBox_1factParam->setChecked(checked);
    ui->textEdit_1factParam->setEnabled(checked);
    ui->textEdit_1controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_checkBox_2controlledParam_clicked(bool checked)
{
    ui->checkBox_2factParam->setChecked(checked);
    ui->textEdit_2factParam->setEnabled(checked);
    ui->textEdit_2controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_checkBox_3controlledParam_clicked(bool checked)
{
    ui->checkBox_3factParam->setChecked(checked);
    ui->textEdit_3factParam->setEnabled(checked);
    ui->textEdit_3controlledParam->setEnabled(checked);
}

void createNewAttestationDocumentDialog::on_pushButton_save_clicked()
{
    if(ui->checkBox_doPrint->isChecked())
    {
        m_document = m_documentPattern.arg(8)
                                      .arg(ui->lineEdit_deputyChiefOfWorkshop->text())
                                      .arg(ui->lineEdit_chiefOfTB->text())
                                      .arg(ui->lineEdit_chiefOfBTC->text())
                                      .arg(ui->lineEdit_mechanic->text())
                                      .arg(ui->lineEdit_model->text())
                                      .arg(ui->lineEdit_inventoryNumber->text())
                                      .arg(ui->lineEdit_type->text())
                                      .arg(ui->lineEdit_designation->text())
                                      .arg(ui->lineEdit_detailName->text())
                                      .arg(ui->spinBox_operationNumber->value(), 3, 10, QChar('0'))
                                      .arg(ui->lineEdit_operationName->text())
                                      .arg(ui->textEdit_1controlledParam->toHtml())
                                      .arg(ui->textEdit_2controlledParam->toHtml())
                                      .arg(ui->textEdit_3controlledParam->toHtml())
                                      .arg(ui->textEdit_1factParam->toHtml())
                                      .arg(ui->textEdit_2factParam->toHtml())
                                      .arg(ui->textEdit_3factParam->toHtml())
                                      .arg("апрель 2016")
                                      .arg(ui->lineEdit_numberInPlan->text());

        //        m_printDialog->setWindowTitle("Печать акта аттестации");
        //        m_printDialog->exec();
/****************************************************************************************/
        QTextDocument document;
        QPrinter *printer = new QPrinter(QPrinter::HighResolution);
        printer->setDocName("Акт аттестации станка с инв. номером " + ui->lineEdit_inventoryNumber->text());
        printer->setPrintProgram(this->windowTitle());
        printer->setFullPage(true);
        printer->setPaperSize(QPrinter::A4);
        printer->setOrientation(QPrinter::Portrait);
        printer->setPageMargins(5, 5, 5, 5, QPrinter::Millimeter);
        printer->setOutputFormat(QPrinter::PdfFormat);
        printer->setOutputFileName("test.pdf");
        document.setHtml(m_document);
        document.print(printer);
        delete printer;
/****************************************************************************************/
    }
    this->accept();
}

void createNewAttestationDocumentDialog::on_pushButton_cancel_clicked()
{
    this->reject();
}

void createNewAttestationDocumentDialog::on_toolButton_degreeSymbol_clicked()
{
    if(m_lastActiveWidgetIsLineEdit)
    {
        m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toHtml()+"°");
    }
}

void createNewAttestationDocumentDialog::on_toolButton_multiplicationSymbol_clicked()
{
    if(m_lastActiveWidgetIsLineEdit)
    {
        m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toHtml()+"×");
    }
}

void createNewAttestationDocumentDialog::on_toolButton_plusMinusSymbol_clicked()
{
    if(m_lastActiveWidgetIsLineEdit)
    {
        m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toHtml()+"±");
    }
}

void createNewAttestationDocumentDialog::on_toolButton_diameterSymbol_clicked()
{
    if(m_lastActiveWidgetIsLineEdit)
    {
        m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toHtml()+"Ø");
    }
}

void createNewAttestationDocumentDialog::on_toolButton_lowerIndex_clicked()
{
    bool isOk = false;
    QString lowerIndex;
    if(m_lastActiveWidgetIsLineEdit)
    {
        lowerIndex = QInputDialog::getText(this, "Нижнее отклонение", "Введите нижнее отклонение со знаком", QLineEdit::Normal, "", &isOk);
        if(isOk&&(!lowerIndex.isEmpty()))
        {
            m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toPlainText() + QString("<sub>%1</sub>").arg(lowerIndex));
        }
    }
}

void createNewAttestationDocumentDialog::on_toolButton_upperIndex_clicked()
{
    bool isOk = false;
    QString upperIndex;
    if(m_lastActiveWidgetIsLineEdit)
    {
        upperIndex = QInputDialog::getText(this, "Верхнее отклонение", "Введите верхнее отклонение со знаком", QLineEdit::Normal, "", &isOk);
        if(isOk&&(!upperIndex.isEmpty()))
        {
            m_lastActiveLineEdit->setHtml(m_lastActiveLineEdit->toPlainText() + QString("<sup>%1</sup>").arg(upperIndex));
        }
    }
}

void createNewAttestationDocumentDialog::m_slotChooseMachine()
{
    m_machinesDialog->exec();
}

void createNewAttestationDocumentDialog::m_slotChooseDetail()
{
    m_detailsDialog->exec();
}

void createNewAttestationDocumentDialog::m_slotChooseComission()
{

}

void createNewAttestationDocumentDialog::m_slotNewMachine(const bool isOk, const int number, const QString inventoryNumber, const QString type, const QString operationName, const QString model, const int group)
{
    if(isOk)
    {
        ui->lineEdit_numberInPlan->setText(QString::number(number));
        ui->lineEdit_inventoryNumber->setText(inventoryNumber);
        ui->lineEdit_type->setText(type);
        ui->lineEdit_operationName->setText(operationName);
        ui->lineEdit_model->setText(model);
        ui->lineEdit_group->setText(QString::number(group));
    }
}

void createNewAttestationDocumentDialog::m_slotNewDetail(const bool isOk, const QString detailDesignation, const QString detailName)
{
    if(isOk)
    {
        ui->lineEdit_designation->setText(detailDesignation);
        ui->lineEdit_detailName->setText(detailName);
    }
}

void createNewAttestationDocumentDialog::on_toolButton_clear1factParam_clicked()
{
    ui->textEdit_1factParam->clear();
}

void createNewAttestationDocumentDialog::on_toolButton_clear2factParam_clicked()
{
    ui->textEdit_2factParam->clear();
}

void createNewAttestationDocumentDialog::on_toolButton_clear3factParam_clicked()
{
    ui->textEdit_3factParam->clear();
}

void createNewAttestationDocumentDialog::on_toolButton_clear1controlledParam_clicked()
{
    ui->textEdit_1controlledParam->clear();
}

void createNewAttestationDocumentDialog::on_toolButton_clear2controlledParam_clicked()
{
    ui->textEdit_2controlledParam->clear();
}

void createNewAttestationDocumentDialog::on_toolButton_clear3controlledParam_clicked()
{
    ui->textEdit_3controlledParam->clear();
}
