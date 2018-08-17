#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(this->ui->prg_pages, SIGNAL(valueChanged(int)), this, SLOT(updatePrgSlider(int)));
    connect(this->ui->chr_pages, SIGNAL(valueChanged(int)), this, SLOT(updateChrSlider(int)));

    connect(ui->prgRamPresent, SIGNAL(clicked(bool)), this, SLOT(enablePrgRam(bool)));
    connect(ui->battery, SIGNAL(clicked(bool)), this, SLOT(enablePrgRam(bool)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile(){
    int version;
    QFileDialog dialog;
    // dialog.setDirectory(QDir::homePath());
    QString file = dialog.getOpenFileName(this,
            tr("Open NES file."), QDir::homePath(),
            tr("NES file (*.nes);;All Files (*)"));
    if(file.isEmpty()){
        return;
    }
    this->nesFullPath = file.toStdString();

    this->ui->text_fullpath->clear();
    this->ui->text_fullpath->insert(file);

    QStringList splitted = file.split("/");
    if(!splitted.isEmpty()){
        this->nesFileName = splitted.last().toStdString();
        this->ui->text_filename->clear();
        this->ui->text_filename->insert(splitted.last());
    }

    this->nesRom = new NesRomParser(this->nesFullPath);

    version = this->nesRom->getVersion();

    this->ui->version->clear();
    this->ui->version->insert(QString::number(version));

    // this->ui->text_prg_size->clear();
    // this->ui->text_prg_size->insert(QString::number(this->nesRom->getPrgSize()));
    // this->ui->text_prg_size->setEnabled(true);
    this->ui->prg_pages->clear();
    this->ui->prg_pages->setValue(this->nesRom->getPrgPages());
    this->ui->prg_pages->setEnabled(true);

    // this->ui->text_chr_size->clear();
    // this->ui->text_chr_size->insert(QString::number(this->nesRom->getChrSize()));
    // this->ui->text_chr_size->setEnabled(true);
    this->ui->chr_pages->clear();
    this->ui->chr_pages->setValue(this->nesRom->getChrPages());
    this->ui->chr_pages->setEnabled(true);

    this->ui->mapper->clear();
    this->ui->mapper->setValue(this->nesRom->getMapper());
    this->ui->mapper->setReadOnly(false);
    this->ui->mapper->setEnabled(true);
    if(version == 2){
        this->ui->mapper->setMaximum(4095);
    }
    else if(version == 1){
        this->ui->mapper->setMaximum(255);
    }
    else{
        this->ui->mapper->setMaximum(15);
    }

    this->ui->submapper->clear();
    this->ui->submapper->setValue(this->nesRom->getSubMapper());
    if(version == 2){
        this->ui->submapper->setReadOnly(false);
        this->ui->submapper->setEnabled(true);
    }
    else{
        this->ui->submapper->setReadOnly(true);
        this->ui->submapper->setEnabled(false);
    }

    this->ui->battery->setChecked(this->nesRom->hasBattery());
    this->ui->battery->setEnabled(true);
    this->ui->trainer->setChecked(this->nesRom->hasTrainer());
    this->ui->trainer->setEnabled(true);
    this->ui->mirroring_orientation->setCurrentIndex(this->nesRom->hasMirroring());
    this->ui->mirroring_orientation->setEnabled(true);
    this->ui->ignore_mirroring->setChecked(this->nesRom->isIgnoreMirroring());
    this->ui->ignore_mirroring->setEnabled(true);

    this->ui->vs->setChecked(this->nesRom->isVs());
    this->ui->pc10->setChecked(this->nesRom->isPC10());
    if(version >= 1 && version <= 2){
        this->ui->vs->setEnabled(true);
        this->ui->pc10->setEnabled(true);
    }

    this->ui->prg_ram->clear();
    this->ui->prg_ram->setValue(this->nesRom->getPrgRamSize());
    if(version == 1 && nesRom->isPrgRamPresent()){
        this->ui->prg_ram->setEnabled(true);
    }
    else{
        this->ui->prg_ram->setEnabled(false);
    }

    this->ui->tv_system->setCurrentIndex(this->nesRom->getTvSystem()?1:0);
    this->ui->dual->setChecked(this->nesRom->isDual());
    if(version == 1 || version == 2){
        this->ui->tv_system->setEnabled(true);
        this->ui->dual->setEnabled(true);
    }

    this->ui->prgRamPresent->setChecked(this->nesRom->isPrgRamPresent());
    this->ui->busConflicts->setChecked(this->nesRom->hasBusConflicts());
    if(version == 1){
        this->ui->prgRamPresent->setEnabled(true);
        this->ui->busConflicts->setEnabled(true);
    }

    this->ui->batteryBackedAmount->clear();
    this->ui->batteryBackedAmount->setValue(this->nesRom->getBatteryBacked());
    this->ui->notBatteryBackedAmount->clear();
    this->ui->notBatteryBackedAmount->setValue(this->nesRom->getNotBatteryBacked());
    if(version == 2){
        this->ui->batteryBackedAmount->setEnabled(true);
        this->ui->notBatteryBackedAmount->setEnabled(true);
    }

    this->ui->chrBatteryBackedAmount->clear();
    this->ui->chrBatteryBackedAmount->setValue(this->nesRom->getChrRamBatteryBacked());
    this->ui->chrNotBatteryBacked->clear();
    this->ui->chrNotBatteryBacked->setValue(this->nesRom->getChrRamNotBatteryBacked());
    if(version == 2){
        this->ui->chrBatteryBackedAmount->setEnabled(true);
        this->ui->chrNotBatteryBacked->setEnabled(true);
    }

    this->ui->vsPPU->setCurrentIndex(this->nesRom->getVsPPU());
    this->ui->vsMode->setCurrentIndex(this->nesRom->getVsMode());
    if(version == 2){
        this->ui->vsPPU->setEnabled(true);
        this->ui->vsMode->setEnabled(true);
    }

    this->ui->miscRoms->clear();
    this->ui->miscRoms->setValue(this->nesRom->getMisc());
    if(version == 2){
        this->ui->miscRoms->setEnabled(true);
    }
}

void MainWindow::updateRomSizes(QLineEdit *edit_box, int size){
    edit_box->clear();
    edit_box->insert(QString::number(size));
    edit_box->insert(" B / ");
    edit_box->insert(QString::number(size/1024));
    edit_box->insert(" KiB");

    if((size/1024/1024) >= 1){
        edit_box->insert(" / ");
        edit_box->insert(QString::number((double)size/1024/1024));
        edit_box->insert(" MiB");
    }
}

void MainWindow::updatePrgSlider(int signal){
    updateRomSizes(this->ui->text_prg_size, this->nesRom->getPrgSize(signal));
    updateRomSizes(this->ui->prg_plus_chr, this->nesRom->getPrgSize(signal) + nesRom->getChrSize(ui->chr_pages->value()));
}

void MainWindow::updateChrSlider(int signal){
    updateRomSizes(this->ui->text_chr_size, this->nesRom->getChrSize(signal));
    updateRomSizes(this->ui->prg_plus_chr, this->nesRom->getChrSize(signal) + nesRom->getPrgSize(ui->prg_pages->value()));
}

void MainWindow::enablePrgRam(bool signal){
    bool enable = nesRom->getVersion() == 1 && ui->prgRamPresent->isChecked() && ui->battery->isChecked() && signal;
    ui->prg_ram->setEnabled(enable);
    ui->label_prg_ram_size->setEnabled(enable);
}
