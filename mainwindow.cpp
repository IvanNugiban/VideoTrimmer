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

    QPalette defaultPalette{};
    defaultPalette.setColor(QPalette::Window, Qt::white);
    this->setPalette(defaultPalette);

    this->acceptDrops();
    ui->stackedWidget->setCurrentIndex(noFilesPage);

    QObject::connect(QApplication::instance(), SIGNAL(focusChanged(QWidget *, QWidget *)), this, SLOT(on_focus_changed(QWidget *, QWidget *)));
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

void MainWindow::on_actionRemove_triggered()
{
    fileManager->removeFile(selectedFileIndex);
    selectedFileIndex = -1;

    toggleUi();
    drawFiles();
}

void MainWindow::on_focus_changed(QWidget *old, QWidget *now)
{
    auto* oldFileItem = qobject_cast<FileItem*>(old);
    auto* newFileItem = qobject_cast<FileItem*>(now);

    auto* layout = ui->scrollAreaWidgetContents->layout();

    if (oldFileItem) {
        oldFileItem->focusout();
    }

    if (newFileItem) {

        newFileItem->focus();

        for (int i = 0; i < layout->count(); ++i)
        {
            QWidget *widget = layout->itemAt(i)->widget();
            if (widget == newFileItem)
            {
                selectedFileIndex = i;
                break;
            }
        }
    }

    else selectedFileIndex = -1;

    toggleSelectedUi();
}

void MainWindow::toggleUi() {
    bool hasFiles = fileManager->getFilesNum() > 0;

    ui->stackedWidget->setCurrentIndex(hasFiles ? filesPage : noFilesPage);
    ui->actionClear->setEnabled(hasFiles);

    toggleSelectedUi();
}

void MainWindow::toggleSelectedUi()
{
    bool fileSelected =  selectedFileIndex != -1;
    ui->actionRemove->setEnabled(fileSelected);
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





