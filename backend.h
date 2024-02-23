#ifndef BACKEND_H
#define BACKEND_H

#include "filemanager.h"

namespace Backend {
    void CutVideo(const MediaFile* mediaFile);
    QString SaveFilePrompt();
    QStringList AddFilesPromt();
    int GetVideoLength(const QString& path);
    int PercentToLength(int value, float max);
}

#endif
