#include "mainwindowgame.h"

#include <QApplication>
#include<QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindowGame w;
    w.show();
    return a.exec();
}
