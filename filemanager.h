#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QStringList>
#include <vector>
#include <QFile>

class FileManager
{
public:

    FileManager() = default;
    ~FileManager();

    void addFiles(const QString& fileName);
    void addFiles(const QStringList& fileNames);

    int getFilesNum();

private:

    // Files array, type of files undecided for now
    std::vector<QFile*> files{};

    bool isFileValid(const QFile* file);

};

#endif
