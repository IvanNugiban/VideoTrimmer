#ifndef FILEITEM_H
#define FILEITEM_H

#include <QWidget>
#include <QFileInfo>
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FileItem;
}
QT_END_NAMESPACE

class FileItem : public QWidget
{
    Q_OBJECT
public:

    FileItem(QWidget *parent = nullptr, MediaFile* info = nullptr);
    ~FileItem();

    void focus();
    void focusout();

    bool locked();
    void toggleLock();

    void setSlider(int lowPercent, int highPercent);
    void cutVideo();

private:

   Ui::FileItem* ui;
   MediaFile* mediaFile;
   QFileInfo fileInfo;

   void setupUi();
   void setMediaFile(int min, int max);

   // If file item is locked, then it will not be affected by main slider that changes all sliders.
   bool isLocked{false};

private slots:

   void on_slider_moved(int min, int max);
    void on_pushButton_clicked();
};

#endif // FILEITEM_H
