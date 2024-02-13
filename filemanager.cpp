#include "filemanager.h"

void FileManager::addFile(int file) {
    files.push_back(file);
}

int FileManager::getFilesNum() {
    return static_cast<int>(files.size());
}
