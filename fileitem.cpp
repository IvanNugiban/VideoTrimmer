#include "fileitem.h"
#include "./ui_fileitem.h"
#include "constants.h"

FileItem::FileItem(QWidget *parent, MediaFile* info)
    : QWidget(parent)
    , ui(new Ui::FileItem)
{
    ui->setupUi(this);
    mediaFile = info;
    fileInfo = QFileInfo{*(mediaFile->file)};

    this->setAutoFillBackground(true);

    setupUi();
}

FileItem::~FileItem()
{
    delete ui;
}

void FileItem::focus()
{
    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Constants::focusedColor);

    this->setPalette(pal);
}

void FileItem::focusout()
{
    QPalette pal = QPalette();

    pal.setColor(QPalette::Window, Qt::transparent);

    this->setPalette(pal);
}

void FileItem::setupUi()
{
    ui->file_name->setText(fileInfo.fileName());
}
