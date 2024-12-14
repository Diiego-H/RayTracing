#include <QApplication>

#include "Controller.hh"
#include "GUI/MainWindow.hh"

// initializing instancePtr with NULL
Controller* Controller ::instancePtr = NULL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowTitle("GiVD 1a pràctica: GPU 2023-24");
    w.show();

    return a.exec();
}

