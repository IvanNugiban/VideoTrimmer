#include "fileitem.h"
#include "./ui_fileitem.h"

FileItem::FileItem(QWidget *parent, MediaFile* info)
    : QWidget(parent)
    , ui(new Ui::FileItem)
{
    ui->setupUi(this);
    mediaFile = info;
    fileInfo = QFileInfo{*(mediaFile->file)};

    setupUi();
}

FileItem::~FileItem()
{
    delete ui;
}

void FileItem::setupUi()
{
    ui->file_name->setText(fileInfo.fileName());
}
