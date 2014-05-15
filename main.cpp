#include <iostream>
#include "db.h"
#include "parser.h"
#include "mainwindow.h"
#include <qapplication.h>
using namespace std;
int main(int argc, char* argv[])
{
    QApplication a(argc,argv);
    MainWindow window;
    window.show();
    return a.exec();
}
