#include "mainwidget.h"
#include <QApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWidget m;
    m.show();

    return a.exec();
}
