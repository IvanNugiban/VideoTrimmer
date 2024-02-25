#ifndef BACKEND_H
#define BACKEND_H

#include "filemanager.h"
#include <vector>

namespace Backend {
    void initialize();
    void cutVideo(const MediaFile* mediaFile, QString fileName = "");
    void cutVideos(const std::vector<MediaFile*>& files);
    QString createThumbnail(const QString& filePath, int id);
    QString saveFilePrompt();
    QString getDirectoryPrompt();
    QStringList addFilesPrompt();
    int getVideoLength(const QString& path);
    int percentToLength(int value, float max);
}

#endif
