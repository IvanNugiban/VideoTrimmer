#include "filemanager.h"
#include <QFileInfo>
#include <QMessageBox>
#include <algorithm>
#include "constants.h"

FileManager::~FileManager() {
    for (auto* file : files) {
        delete file;
    }
}

void FileManager::addFiles(const QStringList& fileNames) {
    for (auto const& fileName : fileNames) {

        QFile* file = new QFile{fileName};

        QFileInfo fileInfo{*file};

        const auto extensions = Constants::supportedExtensions;

        bool correctExtension = std::find(extensions.begin(), extensions.end(), fileInfo.suffix()) != extensions.end();

        if (!fileInfo.isReadable() || !fileInfo.isWritable() || !correctExtension) {
            QMessageBox::warning(nullptr, "Error", "Invalid file or file extension!");
            continue;
        }

        files.push_back(file);
    }
}

int FileManager::getFilesNum() {
    return static_cast<int>(files.size());
}
