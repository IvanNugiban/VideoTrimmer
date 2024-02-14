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

private:

   Ui::FileItem* ui;
   MediaFile* mediaFile;
   QFileInfo fileInfo;

   void setupUi();

signals:
};

#endif // FILEITEM_H
