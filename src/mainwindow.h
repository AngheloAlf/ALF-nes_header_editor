#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nesromparser.h"
#include <QLineEdit>

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
    void updatePrgSlider(int signal);
    void updateChrSlider(int signal);
    void enablePrgRam(bool signal);

private:
    Ui::MainWindow *ui;
    std::string nesFileName;
    std::string nesFullPath;
    NesRomParser *nesRom;

    void updateRomSizes(QLineEdit *edit_box, int size);

};

#endif // MAINWINDOW_H
