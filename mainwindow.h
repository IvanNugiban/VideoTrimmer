#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FileManager.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:

    virtual void dragEnterEvent(QDragEnterEvent *e) override;
    virtual void dropEvent(QDropEvent *e) override;

private slots:
    void on_actionExit_triggered();

    void on_actionAdd_triggered();

    void on_actionClear_triggered();

private:

    enum pages {
        filesPage,
        noFilesPage
    };

    Ui::MainWindow* ui;

    FileManager* fileManager;

    void toggleUi();
    void drawFiles();
    void clearUi(QLayout *layout);
};
#endif // MAINWINDOW_H
