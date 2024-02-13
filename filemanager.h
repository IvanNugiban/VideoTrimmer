#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>

class FileManager
{
public:

    FileManager() = default;

    void addFile(int file);

    int getFilesNum();

private:

    // Files array, type of files undecided for now
    std::vector<int> files{};

};

#endif
