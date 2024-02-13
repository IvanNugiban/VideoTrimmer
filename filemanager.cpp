#include "filemanager.h"
#include <QFileInfo>
#include <QMessageBox>
#include "constants.h"

FileManager::~FileManager() {
    for (auto* file : files) {
        delete file;
    }
}

void FileManager::addFiles(const QString& fileName) {

    QFile* file = new QFile{fileName};

    if (isFileValid(file)) files.push_back(file);
}

void FileManager::addFiles(const QStringList& fileNames) {
    for (auto const& fileName : fileNames) {

        QFile* file = new QFile{fileName};

        if (!isFileValid(file)) continue;

        files.push_back(file);
    }
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

