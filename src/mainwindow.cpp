#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(){
    QFileDialog dialog;
    // dialog.setDirectory(QDir::homePath());
    QString file = dialog.getOpenFileName(this,
            tr("Open NES file."), QDir::homePath(),
            tr("NES file (*.nes);;All Files (*)"));
    if(file.isEmpty()){
        return;
    }
    this->nesFullPath = file.toStdString();

    this->ui->text_filename->clear();
    this->ui->text_fullpath->insert(file);

    QStringList splitted = file.split("/");
    if(!splitted.isEmpty()){
        this->nesFileName = splitted.last().toStdString();
        this->ui->text_filename->clear();
        this->ui->text_filename->insert(splitted.last());
    }

    this->nesRom = new NesRomParser(this->nesFullPath);

    this->ui->text_prg_size->clear();
    this->ui->text_prg_size->insert(QString::number(this->nesRom->getPrgSize()));

    this->ui->text_chr_size->clear();
    this->ui->text_chr_size->insert(QString::number(this->nesRom->getChrSize()));

}
