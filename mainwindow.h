#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "FileManager.h"

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

private slots:
    void on_actionExit_triggered();

    void on_actionAdd_triggered();

private:

    enum pages {
        filesPage,
        noFilesPage
    };

    Ui::MainWindow* ui;

    FileManager* fileManager;

    void switchPage();
};
#endif // MAINWINDOW_H
