#include "nesromheader.h"
#include <string.h>

extern "C" {
#include "ALF_std.h"
}

NesRomHeader::NesRomHeader(const char* header, int fileSize){
    this->fileSize = fileSize;

    this->header = (char *)malloc(sizeof(char)*16);
    mempcpy(this->header, header, 16);
    if(!memcmp(this->header, "NES\x1A", 4)){
        // iNES format
        this->headerID = (char *)malloc(sizeof(char)*5);
        memcpy(this->headerID, "NES\x1A", 4);
        this->parseINES();
    }
    else if(!memcmp(this->header, "UNIF", 4)){
        // UNIF format!
        // not recognized.
        // TODO: throw exception
        this->error = true;
        return;
    }
    else{
        // Posibly not a NES rom
        // TODO: throw exception
        this->error = true;
        return;
    }
}


NesRomHeader::~NesRomHeader(){
    // TODO: this
}

void NesRomHeader::parseINES(){
    this->prgSize = this->header[4];
    this->chrSize = this->header[5];
    this->parseInesFlag6();

    // Version detector
    int possiblePrgSize = ((this->header[9] & ALF_LOW_NIBBLE) << 8) + this->prgSize;
    int possibleChrSize = ((this->header[9] & ALF_HIGH_NIBBLE) << 4) + this->prgSize;
    if(((this->header[7] & 0x0C) == 0x08) && ((possiblePrgSize*16 + possibleChrSize*8) < this->fileSize)){
        this->version = 2;
    }
    else if(((this->header[7] & 0x0C) == 0x00) && !this->header[12] && (!this->header[13] && !this->header[14] && !this->header[15])){
        this->version = 1;
    }
    else{
        this->version = 0;
    }

    this->parseInesFlag7();
    this->parseInesFlag8();
    this->parseInesFlag9();
    this->parseInesFlag10();
    this->parseInesFlag11();
    this->parseInesFlag12();
    this->parseInesFlag13();
    this->parseInesFlag14();
    this->parseInesFlag15();
}

void NesRomHeader::parseInesFlag6(){

    this->mirroring = ALF_GET_BIT(this->header[6], 0);
    this->battery = ALF_GET_BIT(this->header[6], 1);
    this->trainer = ALF_GET_BIT(this->header[6], 2);
    this->ignoreMirroring = ALF_GET_BIT(this->header[6], 3);

    this->mapper = (this->header[6] & ALF_HIGH_NIBBLE) >> 4;

}

void NesRomHeader::parseInesFlag7(){
    if(this->version == 2 || this->version == 1){
        this->vsUnisystem = ALF_GET_BIT(this->header[7], 0);
        this->pc10 = ALF_GET_BIT(this->header[7], 1);
        this->mapper += this->header[7] & ALF_HIGH_NIBBLE;
    }
}

void NesRomHeader::parseInesFlag8(){
    if(this->version == 2){
        this->submapper = (this->header[8] & ALF_HIGH_NIBBLE) >> 4;
        this->mapper += (this->header[8] & ALF_LOW_NIBBLE) << 8;
    }
    else if(this->version == 1){
        this->prgRamSize = this->header[8];
    }
}

void NesRomHeader::parseInesFlag9(){
    if(this->version == 2){
        this->prgSize += (this->header[9] && ALF_LOW_NIBBLE) << 8;
        this->chrSize += (this->header[9] && ALF_HIGH_NIBBLE) << 4;
    }
    else if(this->version == 1){
        this->tvSystem = ALF_GET_BIT(this->header[9], 0);
    }
}

void NesRomHeader::parseInesFlag10(){
    if(this->version == 2){
        this->batteryBacked = (ALF_HIGH_NIBBLE & this->header[10])>>4;
        this->notBatteryBacked = (ALF_LOW_NIBBLE & this->header[10]);
    }
    else if(this->version == 1){
        this->dual = ALF_GET_BIT(this->header[10], 0);
        this->pal = ALF_GET_BIT(this->header[10], 1);
        this->prgRamPresent = ALF_GET_BIT(this->header[10], 4);
        this->busConflicts = ALF_GET_BIT(this->header[10], 5);
    }
}

void NesRomHeader::parseInesFlag11(){
    if(this->version == 2){
        this->chrRamBatteryBacked = (ALF_HIGH_NIBBLE & this->header[11])>>4;
        this->chrRamNotBatteryBacked = (ALF_LOW_NIBBLE & this->header[11]);
    }
}

void NesRomHeader::parseInesFlag12(){
    if(this->version == 2){
        this->pal = ALF_GET_BIT(this->header[12], 0);
        this->dual = ALF_GET_BIT(this->header[12], 1);

        this->tvSystem = this->pal;
    }
}

void NesRomHeader::parseInesFlag13(){
    if(this->version == 2){
        this->chrRamBatteryBacked = (ALF_HIGH_NIBBLE & this->header[11])>>4;
        this->chrRamNotBatteryBacked = (ALF_LOW_NIBBLE & this->header[11]);
    }
}

void NesRomHeader::parseInesFlag14(){
    if(this->version == 2){
        this->misc = ALF_GET_BIT(this->header[14], 1) | ALF_GET_BIT(this->header[14], 0);
    }
}

void NesRomHeader::parseInesFlag15(){
    // void
}

int NesRomHeader::getPrgPages(){
    return this->prgSize;
}
int NesRomHeader::getChrPages(){
    return this->chrSize;
}
int NesRomHeader::getPrgSize(){
    return this->prgSize*PRG_ROM_SIZE;
}
int NesRomHeader::getPrgSize(unsigned int pages){
    return pages*PRG_ROM_SIZE;
}
int NesRomHeader::getChrSize(){
    return this->chrSize*CHR_ROM_SIZE;
}
int NesRomHeader::getChrSize(unsigned int pages){
    return pages*CHR_ROM_SIZE;
}

bool NesRomHeader::hasMirroring(){
    return this->mirroring;
}
bool NesRomHeader::hasBattery(){
    return this->battery;
}
bool NesRomHeader::hasTrainer(){
    return this->trainer;
}
bool NesRomHeader::isIgnoreMirroring(){
    return this->ignoreMirroring;
}

int NesRomHeader::getMapper(){
    return this->mapper;
}
int NesRomHeader::getSubMapper(){
    return this->submapper;
}

bool NesRomHeader::isVs(){
    return this->vsUnisystem;
}
bool NesRomHeader::isPC10(){
    return this->pc10;
}

char NesRomHeader::getPrgRamSize(){
    return this->prgRamSize;
}
bool NesRomHeader::getTvSystem(){
    return this->tvSystem;
}
bool NesRomHeader::isPal(){
    return this->pal;
}
bool NesRomHeader::isDual(){
    return this->dual;
}
bool NesRomHeader::isPrgRamPresent(){
    return this->prgRamPresent;
}
bool NesRomHeader::hasBusConflicts(){
    return this->busConflicts;
}

char NesRomHeader::getBatteryBacked(){
    return this->batteryBacked;
}
char NesRomHeader::getNotBatteryBacked(){
    return this->notBatteryBacked;
}

char NesRomHeader::getChrRamBatteryBacked(){
    return this->chrRamBatteryBacked;
}
char NesRomHeader::getChrRamNotBatteryBacked(){
    return this->chrRamNotBatteryBacked;
}

char NesRomHeader::getVsPPU(){
    return this->vsPPU;
}
char NesRomHeader::getVsMode(){
    return this->vsMode;
}
char NesRomHeader::getMisc(){
    return this->misc;
}

char NesRomHeader::getVersion(){
    return this->version;
}


