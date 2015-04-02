#ifndef ONELINETEXTEDIT_H
#define ONELINETEXTEDIT_H

//
// original links:
// http://qt-project.org/faq/answer/how_can_i_create_a_one-line_qtextedit#350
// http://qt-project.org/faq/answer/how_can_i_create_a_one-line_qtextedit#685
//

#include <QtCore>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#include <QtGui>
#include <QKeyEvent>
#include <QWheelEvent>

class OneLineTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit OneLineTextEdit(QWidget *parent = 0);
    ~OneLineTextEdit();

    QSize sizeHint() const;

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void wheelEvent(QWheelEvent *e);
};
#endif // ONELINETEXTEDIT_H
