#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "fileitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), fileManager{new FileManager{}}
{
    ui->setupUi(this);

    this->acceptDrops();
    ui->stackedWidget->setCurrentIndex(noFilesPage);
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

    toggleUi();
    drawFiles();
}

void MainWindow::on_actionClear_triggered()
{
    clearUi(ui->scrollAreaWidgetContents->layout());
    fileManager->clearFiles();
    toggleUi();
}

void MainWindow::toggleUi() {
    bool hasFiles = fileManager->getFilesNum() > 0;

    ui->stackedWidget->setCurrentIndex(hasFiles ? filesPage : noFilesPage);
    ui->actionClear->setEnabled(hasFiles);
}

void MainWindow::drawFiles()
{
    auto layout = ui->scrollAreaWidgetContents->layout();

    clearUi(layout);

    auto files = fileManager->getFiles();

    for (auto* mediaFile : files) {
        FileItem* fileItem = new FileItem{this, mediaFile};

        layout->addWidget(fileItem);
    }
}

void MainWindow::clearUi(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearUi(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
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

    toggleUi();
    drawFiles();
}


