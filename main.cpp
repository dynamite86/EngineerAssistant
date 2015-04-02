#include "mainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTranslator qtTranslator;
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Windows"));

//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#if QT_VERSION >= 0x050000
    qtTranslator.load("./translations/qtbase_" + QLocale::system().name());
#else
    qtTranslator.load("./translations/qt_" + QLocale::system().name());
#endif

    a.installTranslator(&qtTranslator);
    mainWindow w;
    w.show();

    return a.exec();
}
