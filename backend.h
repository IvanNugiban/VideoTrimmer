#ifndef BACKEND_H
#define BACKEND_H

#include "filemanager.h"
#include <vector>

namespace Backend {
    void cutVideo(const MediaFile* mediaFile, QString fileName = "");
    void cutVideos(const std::vector<MediaFile*>& files);
    QString saveFilePrompt();
    QString getDirectoryPrompt();
    QStringList addFilesPrompt();
    int getVideoLength(const QString& path);
    int percentToLength(int value, float max);
}

#endif
