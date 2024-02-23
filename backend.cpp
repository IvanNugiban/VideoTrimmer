#include "backend.h"
#include <QProcess>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include "constants.h"

namespace Backend {
void cutVideo(const MediaFile* mediaFile, QString output)
    {
        QFileInfo fileInfo{*mediaFile->file};

        QString inputPath{fileInfo.filePath()};
        QString outputPath{output};

        if (output == "") outputPath = saveFilePrompt();

        if (outputPath == "") return;

        QString cutMin{QString::number(Backend::percentToLength(mediaFile->cutMin, mediaFile->duration))};
        QString cutMax{QString::number(Backend::percentToLength(mediaFile->cutMax, mediaFile->duration))};
        QProcess process;


        process.start("D:\\Coding\\VideoTrimmer\\VideoTrimmer\\lib\\ffmpeg\\bin\\ffmpeg.exe",
                      QStringList() <<  "-y" << "-i" << inputPath << "-ss" << cutMin << "-to"  << cutMax << "-c:v" << "copy" << "-c:a" << "copy"  << outputPath) ;

        if (!process.waitForStarted()) {
            qDebug() << "error:" << process.errorString();
            return;
        }

        process.waitForFinished();
    }

    void cutVideos(const std::vector<MediaFile *> &files)
    {
        QString dir = getDirectoryPrompt();

        if (dir == "") return;

        for (int i{0}; i < files.size(); i++) {

            QFileInfo fileInfo{*files[i]->file};
            QString fileExt = fileInfo.suffix();

            cutVideo(files[i], dir + '/' + fileInfo.baseName() + " cut" + QString::number(i + 1) + '.' + fileExt);
        }
    }

    QString saveFilePrompt()
    {
        return QFileDialog::getSaveFileName(nullptr, "Save video", "",  QString::fromStdString(Constants::supportedExtensionsExt));
    }

    QString getDirectoryPrompt()
    {
        return QFileDialog::getExistingDirectory(nullptr, "Select directory");
    }

    QStringList addFilesPrompt()
    {
        return  QFileDialog::getOpenFileNames(nullptr, "Select videos", "",  QString::fromStdString(Constants::supportedExtensionsExt));
    }

    int getVideoLength(const QString& path)
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

    int percentToLength(int value, float max)
    {
        return std::round(max / Constants::sliderMaxValue * value);
    }

}
