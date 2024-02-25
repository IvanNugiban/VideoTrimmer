#include "fileitem.h"
#include "./ui_fileitem.h"
#include "constants.h"
#include "backend.h"

FileItem::FileItem(QWidget *parent, MediaFile* info)
    : QWidget(parent)
    , ui(new Ui::FileItem)
{
    ui->setupUi(this);
    ui->cut_controls->setup(info->duration, info->cutMin, info->cutMax);
    ui->thumbnail->setPixmap(info->thumbnail);

    mediaFile = info;

    fileInfo = QFileInfo{*(mediaFile->file)};
    this->setAutoFillBackground(true);

    setupUi();

    QObject::connect(ui->cut_controls->getSlider(), SIGNAL(sliderMoved(int, int)), this, SLOT(on_slider_moved(int,int)));
}

FileItem::~FileItem()
{
    delete ui;
}

void FileItem::on_slider_moved(int min, int max)
{
    setMediaFile(min, max);
}

void FileItem::on_pushButton_clicked()
{
    cutVideo();
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

bool FileItem::locked()
{
    return isLocked;
}

void FileItem::setSlider(int lowPercent, int highPercent)
{
    ui->cut_controls->setSlider(lowPercent, highPercent);
    setMediaFile(lowPercent, highPercent);
}

void FileItem::cutVideo()
{
    Backend::cutVideo(mediaFile);
}

void FileItem::setupUi()
{
    ui->file_name->setText(fileInfo.fileName());
}

void FileItem::setMediaFile(int min, int max)
{
    mediaFile->cutMin = min;
    mediaFile->cutMax = max;
}

void FileItem::toggleLock()
{
    isLocked = !isLocked;
}


