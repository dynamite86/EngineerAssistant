/***************************************************************************************************************
  Модуль расширения для класса QTableWidget.
  Автор: dynamite, 2012...2014
  Версия: 0.5
***************************************************************************************************************/

#ifndef _MYTABLEWIDGET_
#define _MYTABLEWIDGET_

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>

class myTableWidget : public QTableWidget
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void RMBReleaseSignal(QPoint);
    void LMBDoubleClickSignal();
    void mouseOverSignal(QPoint, qint32, qint32);
    void cellToolButtonClicked();

private slots:
    void pSlotCellWasChanged(int row, int column);
    void pSlotCurrentCellWasChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void pSlotItemSelectionChanged();

private:
    // флаг автоматического изменения высоты строк под содержащиеся в них данные
    // true  - изменение высоты включено;
    // false - изменение высоты отключено;
    bool pAutoResizeRowsEnabled;

    // флаг автоматического изменения ширины столбцов под содержащиеся в них данные
    // true  - изменение ширины включено;
    // false - изменение ширины отключено;
    bool pAutoResizeColumnsEnabled;

    bool pUsingCellWidgets;
    int pWidgetColumn;

    QLineEdit *pCellEditField;
    QAction *pCellEditFieldAction;

    // проверка ячейки на заполненность
    bool pCellIsEmpty(const int row, const int column);

    // установка данных для указанной ячейки
    void pSetCellData(const int row, const int column, const QString &data);

    // получение данных для указанной ячейки
    QString pCellData(const int row, const int column);

    // удаление строк
    void pDeleteRows();

    void pShowHideCellWidgets();

public:
    explicit myTableWidget(QWidget *parent = 0);
    ~myTableWidget();

    // получение значения из указанной ячейки
    // в случае неудачи возвращается пустой контейнер
    QVariant cellContent(const int row, const int column);

    // установка значения для указанной ячейки
    bool setCellContent(const int row, const int column, const QString  &data);
    bool setCellContent(const int row, const int column, const char     *data);
    bool setCellContent(const int row, const int column, const QVariant &data);

    //добавление новой строки в конец таблицы
    bool appendRow(const QStringList &data = QStringList());

    // удаление указанной строки
    bool deleteRow(const int row);

    // удаление всех строк
    void deleteAllRows();

    // получение состояния флага автоматического изменения высоты строк
    bool rowsAutoResize();

    // установка состояния флага автоматического изменения высоты строк
    void setRowsAutoResize(bool state);

    // получение состояния флага автоматического изменения ширины столбцов
    bool columnsAutoResize();

    // установка состояния флага автоматического изменения ширины столбцов
    void setColumnsAutoResize(bool state);

    // включение отображения виджетов для указанного столбца
    bool setToolButtonAtColumn(const int column, const bool show);
};

#endif // _MYTABLEWIDGET_
