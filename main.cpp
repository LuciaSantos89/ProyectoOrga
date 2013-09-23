#include "mainwindow.h"
#include <QApplication>

#include <iostream>

#include <TDARecordFile.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Proyecto Lusilla");
    a.setOrganizationName("Lucia Santos");


    MainWindow w;
    w.show();
   // w.~MainWindow();
    return a.exec();
}
