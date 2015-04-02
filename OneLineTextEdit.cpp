#include "OneLineTextEdit.h"

OneLineTextEdit::OneLineTextEdit(QWidget *parent) : QTextEdit(parent)
{
    setWordWrapMode(QTextOption::NoWrap);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setTabChangesFocus(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}
OneLineTextEdit::~OneLineTextEdit(){}

QSize OneLineTextEdit::sizeHint () const
{
    QFontMetrics fm(font());
    int h = fm.height();
    int w = fm.width(QLatin1Char('x'));

    return QSize(w, h);
}

void OneLineTextEdit::keyPressEvent (QKeyEvent *e)
{
    if((e->key () == Qt::Key_Enter)||(e->key () == Qt::Key_Return))
    {
        e->ignore();
    }
    else
    {
        QTextEdit::keyPressEvent (e);
    }
}

void OneLineTextEdit::wheelEvent(QWheelEvent *e)
{
    e->ignore();
}
