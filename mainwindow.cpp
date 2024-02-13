#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), fileManager{new FileManager{}}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileManager;
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void MainWindow::on_actionAdd_triggered()
{
    fileManager->addFile(1);

    switchPage();
}

void MainWindow::switchPage() {
    ui->stackedWidget->setCurrentIndex(fileManager->getFilesNum() == 0 ? noFilesPage : filesPage);
}
