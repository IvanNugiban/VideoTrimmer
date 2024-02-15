#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QStringList>
#include <vector>
#include <QFile>

struct MediaFile {
    QFile* file;
    int cutMin{0};
    int cutMax{99};
};

class FileManager
{
public:

    FileManager() = default;
    ~FileManager();

    void addFiles(const QString& fileName);
    void addFiles(const QStringList& fileNames);
    void removeFile(int index);
    void clearFiles();

    std::vector<MediaFile*>& getFiles();
    int getFilesNum();

private:

    // Files array, type of files undecided for now
    std::vector<MediaFile*> files{};

    bool isFileValid(const QFile* file);
};

#endif
