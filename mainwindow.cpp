#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), fileManager{new FileManager{}}
{
    ui->setupUi(this);

    this->acceptDrops();
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

void MainWindow::dragEnterEvent(QDragEnterEvent *e) {

    // If dropped content is files allow to proceed
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{
    for (const auto& url : e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        fileManager->addFiles(fileName);
    }

    switchPage();
}
