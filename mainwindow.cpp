#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), fileManager{new FileManager{}}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void MainWindow::on_actionAdd_triggered()
{
    QStringList filesName = QFileDialog::getOpenFileNames(this, "Select videos", "",  "mp4 (*.mp4)");

    fileManager->addFiles(filesName);

    switchPage();
}

void MainWindow::switchPage() {
    ui->stackedWidget->setCurrentIndex(fileManager->getFilesNum() == 0 ? noFilesPage : filesPage);
}
