/***************************************************************************************************************
  Модуль расширения для класса QTableWidget.
  Автор: dynamite, 2012...2014
  Версия: 0.5
***************************************************************************************************************/

#include "myTableWidget.h"
/********************************************************************************/
/*   P R O T E C T E D    S E C T I O N                                         */
/********************************************************************************/
void myTableWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::RightButton){
        this->RMBReleaseSignal(event->globalPos());
    }
    QTableWidget::mousePressEvent(event);
}

void myTableWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton){
        if(event->type() == QMouseEvent::MouseButtonDblClick){
            this->LMBDoubleClickSignal();
        }
    }
    QTableWidget::mousePressEvent(event);
}

void myTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    QTableWidget::mouseMoveEvent(event);
    if(this->rowCount() > 0){
        this->mouseOverSignal(event->globalPos(), this->rowAt(event->pos().y()), this->columnAt(event->pos().x()));
    }
}

/********************************************************************************/
/*   P R I V A T E    S E C T I O N                                             */
/********************************************************************************/
// проверка ячейки на заполненность
bool myTableWidget::pCellIsEmpty(const int row, const int column)
{
    if(this->item(row, column)){
        if(this->item(row, column)->text().isEmpty()){
            return true;
        }else{
            return false;
        }
    }
    return true;
}

// установка данных для указанной ячейки
void myTableWidget::pSetCellData(const int row, const int column, const QString &data)
{
    if(pUsingCellWidgets)
    {
        if((QLineEdit*)this->cellWidget(row, column))
        {
            ((QLineEdit*)this->cellWidget(row, column))->setText(data);
        }
    }
    else
    {
        if(!this->item(row, column))
        {
            this->setItem(row, column, new QTableWidgetItem);
        }
        this->item(row, column)->setText(data);
    }
}

// получение данных для указанной ячейки
QString myTableWidget::pCellData(const int row, const int column)
{
    QString buffer;
    if(this->item(row, column)){
        buffer = this->item(row, column)->text();
        return buffer;
    }
    return QString();
}

// удаление всех строк
void myTableWidget::pDeleteRows()
{
    for(int i = this->rowCount()-1; i >= 0; i--){
        this->removeRow(i);
    }
}

/********************************************************************************/
/*   P R I V A T E    S L O T S    S E C T I O N                                */
/********************************************************************************/
void myTableWidget::pSlotCellWasChanged(int row, int column)
{
    Q_UNUSED(row);
    Q_UNUSED(column);

    if(pUsingCellWidgets){
        pShowHideCellWidgets();
    }

    if(pAutoResizeRowsEnabled){
        this->resizeRowsToContents();
    }
    if(pAutoResizeColumnsEnabled){
        this->resizeColumnsToContents();
    }
}
void myTableWidget::pSlotCurrentCellWasChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    Q_UNUSED(currentRow);
    Q_UNUSED(currentColumn);
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);

    if(pUsingCellWidgets){
        pShowHideCellWidgets();
    }

    if(pAutoResizeRowsEnabled){
        this->resizeRowsToContents();
    }
    if(pAutoResizeColumnsEnabled){
        this->resizeColumnsToContents();
    }
}
void myTableWidget::pSlotItemSelectionChanged()
{
    if(pAutoResizeRowsEnabled){
        this->resizeRowsToContents();
    }
    if(pAutoResizeColumnsEnabled){
        this->resizeColumnsToContents();
    }
}

// управление отображением QComboBox в ячейках
// если для текущей колонки назначено использование виджета QComboBox, виджет отбражается, в остальных случаях виджет не отображается.
// значение из ячейки отображается в QComboBox, если оно есть в списке виджета, иначе отображается первое значение из списка виджета.
// при скрытии виджета текущее значение из списка виджета отображается в ячейке.
void myTableWidget::pShowHideCellWidgets()
{
    if(pUsingCellWidgets)
    {
        pCellEditField       = new QLineEdit(this);
        pCellEditFieldAction = pCellEditField->addAction(QIcon("qrc:/images/res/images/filecontents-128.png"), QLineEdit::TrailingPosition);
        connect(pCellEditFieldAction, SIGNAL(triggered()), this, SIGNAL(cellToolButtonClicked()));
        for(int row = 0; row < this->rowCount(); row++)
        {
            if(!(QLineEdit*)this->cellWidget(row, pWidgetColumn))
            {
                this->setCellWidget(row, pWidgetColumn, pCellEditField);
            }
        }
    }
    else
    {
        pCellEditField->deleteLater();
        pCellEditFieldAction->deleteLater();
        disconnect(pCellEditFieldAction, SIGNAL(triggered()), this, SIGNAL(cellToolButtonClicked()));
        for(int row = 0; row < this->rowCount(); row++)
        {
            if((QLineEdit*)this->cellWidget(row, pWidgetColumn))
            {
                this->removeCellWidget(row, pWidgetColumn);
            }
        }
    }
}
/********************************************************************************/
/*   P U B L I C    S E C T I O N                                               */
/********************************************************************************/
myTableWidget::myTableWidget(QWidget *parent):QTableWidget(parent)
{
    connect(this, SIGNAL(cellChanged(int,int)),                this, SLOT(pSlotCellWasChanged(int,int)));
    connect(this, SIGNAL(currentCellChanged(int,int,int,int)), this, SLOT(pSlotCellWasChanged(int,int)));
    connect(this, SIGNAL(itemSelectionChanged()),              this, SLOT(pSlotItemSelectionChanged()));
    pAutoResizeRowsEnabled    = false;
    pAutoResizeColumnsEnabled = false;
    pUsingCellWidgets         = false;
    pWidgetColumn             = 0;
    pCellEditField            = 0;
    pCellEditFieldAction      = 0;

}

myTableWidget::~myTableWidget(){}

// получение значения из указанной ячейки
// в случае неудачи возвращается пустой контейнер
QVariant myTableWidget::cellContent(const int row, const int column)
{
    QVariant buffer;
    buffer.clear();

    if((row >= this->rowCount())||(column >= this->columnCount())){
        return buffer;
    }

    if(!pCellIsEmpty(row, column)){
        buffer.setValue(this->pCellData(row, column));
    }
    return buffer;
}

bool myTableWidget::setCellContent(const int row, const int column, const QString &data)
{
    if(data.isEmpty()||(row < 0)||(column < 0)||(row >= this->rowCount())||(column >= this->columnCount())){
        return false;
    }
    this->pSetCellData(row, column, data);
    return true;
}
bool myTableWidget::setCellContent(const int row, const int column, const char *data)
{
    if(!data||(row < 0)||(column < 0)||(row >= this->rowCount())||(column >= this->columnCount())){
        return false;
    }
    this->pSetCellData(row, column, QString(data));
    return true;
}
bool myTableWidget::setCellContent(const int row, const int column, const QVariant &data)
{
    if((!data.isValid())||(row < 0)||(column < 0)||(row >= this->rowCount())||(column >= this->columnCount())){
        return false;
    }
    if(data.canConvert(QVariant::String)){
        this->pSetCellData(row, column, data.toByteArray());
    }
    return true;
}

//добавление новой строки в конец таблицы
bool myTableWidget::appendRow(const QStringList &data)
{
    if(data.isEmpty()){
        this->insertRow(this->rowCount());
        return true;
    }else{
        if((data.size() > this->columnCount())){
            return false;
        }else{
            this->insertRow(this->rowCount());
            for(int i = 0; i < data.size(); i++){
                this->pSetCellData(this->rowCount()-1, i, data.at(i));
            }
            return true;
        }
    }
}

// удаление указанной строки
bool myTableWidget::deleteRow(const int row)
{
    if((row < 0)||(row >= this->rowCount())){
        return false;
    }
    this->removeRow(row);
    //this->rowCountChangedSignal(this->objectName());
    return true;
}

// удаление всех строк
void myTableWidget::deleteAllRows()
{
    pDeleteRows();
    //this->rowCountChangedSignal(this->objectName());
}

// получение состояния флага автоматического изменения высоты строк
bool myTableWidget::rowsAutoResize()
{
    return pAutoResizeRowsEnabled;
}

// получение состояния флага автоматического изменения ширины столбцов
bool myTableWidget::columnsAutoResize()
{
    return pAutoResizeColumnsEnabled;
}

// установка состояния флага автоматического изменения высоты строк
void myTableWidget::setRowsAutoResize(bool state)
{
    pAutoResizeRowsEnabled = state;
    if(state){
        this->resizeRowsToContents();
    }
}

// установка состояния флага автоматического изменения ширины столбцов
void myTableWidget::setColumnsAutoResize(bool state)
{
    pAutoResizeColumnsEnabled = state;
    if(state){
        this->resizeColumnsToContents();
    }
}
// включение отображения виджетов QComboBox для указанного столбца
bool myTableWidget::setToolButtonAtColumn(const int column, const bool show)
{
    if((column >= 0)&&(column < this->columnCount())){
        pWidgetColumn = column;
        pUsingCellWidgets = show;
        pShowHideCellWidgets();
        return true;
    }
    return false;
}
