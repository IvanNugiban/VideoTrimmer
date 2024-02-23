#include "backend.h"
#include <QProcess>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "constants.h"

namespace Backend {
    void CutVideo(const MediaFile* mediaFile)
    {
        QFileInfo fileInfo{*mediaFile->file};

        QString fileExt = fileInfo.suffix();
        QString inputPath{fileInfo.filePath()};
        QString outputPath{SaveFilePrompt()};

        if (outputPath == "") return;

        QString cutMin{QString::number(Backend::PercentToLength(mediaFile->cutMin, mediaFile->duration))};
        QString cutMax{QString::number(Backend::PercentToLength(mediaFile->cutMax, mediaFile->duration))};
        QProcess process;


        process.start("D:\\Coding\\VideoTrimmer\\VideoTrimmer\\lib\\ffmpeg\\bin\\ffmpeg.exe",
                      QStringList() << "-i" << inputPath << "-ss" << cutMin << "-to"  << cutMax << "-c:v" << "copy" << "-c:a" << "copy"  << outputPath) ;

        if (!process.waitForStarted()) {
            qDebug() << "error:" << process.errorString();
            return;
        }

        process.waitForFinished();
    }

    QString SaveFilePrompt()
    {
        return QFileDialog::getSaveFileName(nullptr, "Save video", "",  QString::fromStdString(Constants::supportedExtensionsExt));
    }

    QStringList AddFilesPromt()
    {
        return  QFileDialog::getOpenFileNames(nullptr, "Select videos", "",  QString::fromStdString(Constants::supportedExtensionsExt));
    }

    int GetVideoLength(const QString& path)
    {
        QProcess process;

        process.start("D:\\Coding\\VideoTrimmer\\VideoTrimmer\\lib\\ffmpeg\\bin\\ffprobe.exe",
                      QStringList() << "-v" << "error" << "-show_entries" << "format=duration" << "-of" <<
                          "default=noprint_wrappers=1:nokey=1" << path);

        if (!process.waitForStarted()) {
            qDebug() << "error:" << process.errorString();
            return -1;
        }

        process.waitForFinished();

        return std::floor(process.readAllStandardOutput().toDouble());
    }

    int PercentToLength(int value, float max)
    {
        return std::round(max / Constants::sliderMaxValue * value);
    }




}
