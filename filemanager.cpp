#include "filemanager.h"
#include <QFileInfo>
#include <QMessageBox>
#include "constants.h"
#include "backend.h"

FileManager::~FileManager() {
    clearFiles();
}

void FileManager::addFiles(const QString& fileName, int sliderMin, int sliderMax) {

    QFile* file = new QFile{fileName};

    int videoLength = Backend::getVideoLength(fileName);

    MediaFile* mediaFile = new MediaFile{file, sliderMin, sliderMax, videoLength};

    if (isFileValid(file) && videoLength != -1) {
        files.push_back(mediaFile);
    }
}

void FileManager::addFiles(const QStringList& fileNames, int sliderMin, int sliderMax) {
    for (auto const& fileName : fileNames) {

        QFile* file = new QFile{fileName};

        int videoLength = Backend::getVideoLength(fileName);

        if (!isFileValid(file) || videoLength == -1) continue;

        MediaFile* mediaFile = new MediaFile{file, sliderMin, sliderMax, videoLength};

        files.push_back(mediaFile);
    }
}

void FileManager::removeFile(int index)
{
    files.erase(files.begin() + index);
}

void FileManager::clearFiles()
{
    for (auto const& mediaFile : files) {
        delete mediaFile->file;
        delete mediaFile;
    }

    files.clear();
}

std::vector<MediaFile*>& FileManager::getFiles()
{
    return files;
}

bool FileManager::isFileValid(const QFile* file)
{
    QFileInfo fileInfo{*file};

    const auto extensions = Constants::supportedExtensions;

    bool correctExtension = extensions.find(fileInfo.suffix().toStdString()) != std::string::npos;

    if (!fileInfo.isFile() || !fileInfo.isReadable() || !fileInfo.isWritable() || !correctExtension) {
        QMessageBox::warning(nullptr, "Error", "Invalid file or file extension!\n Allowable extensions: "
                                                   + QString::fromStdString(Constants::supportedExtensions));
        return false;
    }

    return true;
}

int FileManager::getFilesNum() {
    return static_cast<int>(files.size());
}


