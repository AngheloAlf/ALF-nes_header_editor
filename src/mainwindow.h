#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nesromparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openFile();

private:
    Ui::MainWindow *ui;
    std::string nesFileName;
    std::string nesFullPath;
    NesRomParser *nesRom;

};

#endif // MAINWINDOW_H
