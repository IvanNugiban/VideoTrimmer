#ifndef BACKEND_H
#define BACKEND_H

#include "filemanager.h"

namespace Backend {
    void cutVideo(const MediaFile* mediaFile);
    QString saveFilePrompt();
    QStringList addFilesPrompt();
    int getVideoLength(const QString& path);
    int percentToLength(int value, float max);
}

#endif
