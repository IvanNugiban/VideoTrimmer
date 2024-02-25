#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include "constants.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Backend::initialize();

    MainWindow mainWindow{};

    mainWindow.resize({Constants::windowWidth, Constants::windowHeight});
    mainWindow.show();

    return a.exec();
}
