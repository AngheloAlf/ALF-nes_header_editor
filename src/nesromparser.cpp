#include "nesromparser.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ios>
#include <iostream>
#include <fstream>
extern "C" {
#include "ALF_std.h"
}
#include "errno.h"
#include <stdio.h>

NesRomParser::NesRomParser(std::string nesRomFullPath)
{
    this->fullPath = nesRomFullPath;
    this->error = false;
    parseRom();
}

NesRomParser::~NesRomParser(){
    // TODO: this
}


void NesRomParser::parseRom(){
    fprintf(stderr, "%s\n", this->fullPath.c_str());

    struct stat results;
    if (stat(this->fullPath.c_str(), &results) == 0){
        this->fileSize = results.st_size;
    }
    else{
        // TODO: throw exception
        fprintf(stderr, "errno: %i\n", errno);
        this->error = true;
        return;
    }
    std::ifstream nesFile (this->fullPath, std::ios_base::in | std::ios_base::binary);

    this->header = (char *)malloc(sizeof(char)*16);
    if(!nesFile.read(this->header, 16)){
        // TODO: throw exception
        this->error = true;
        free(this->header);
        return;
    }
    /*for(int i  = 0; i< 16; i++){
        fprintf(stderr, "%i 0x%x\n", i, this->header[i]);
    }*/
    // TODO: read the rest of the file and save it.
    nesFile.close();
    this->parseHeader();
}

void NesRomParser::parseHeader(){
    if(!strncmp(this->header, "NES\x1A", 4)){
        // iNES format
        this->headerID = (char *)malloc(sizeof(char)*5);
        strncpy(this->headerID, "NES\x1A", 4);
        this->parseINES();
    }
    else if(!strncmp(this->header, "UNIF", 4)){
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
    // this->headerID = malloc(sizeof);
}

void NesRomParser::parseINES(){
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

void NesRomParser::parseInesFlag6(){

    this->mirroring = ALF_GET_BIT(this->header[6], 0);
    this->battery = ALF_GET_BIT(this->header[6], 1);
    this->trainer = ALF_GET_BIT(this->header[6], 2);
    this->ignoreMirroring = ALF_GET_BIT(this->header[6], 3);

    this->mapper = (this->header[6] & ALF_HIGH_NIBBLE) >> 4;

}

void NesRomParser::parseInesFlag7(){
    if(this->version == 2 || this->version == 1){
        this->vsUnisystem = ALF_GET_BIT(this->header[7], 0);
        this->pc10 = ALF_GET_BIT(this->header[7], 1);
        this->mapper += this->header[7] & ALF_HIGH_NIBBLE;
    }
}

void NesRomParser::parseInesFlag8(){
    if(this->version == 2){
        this->submapper = (this->header[8] & ALF_HIGH_NIBBLE) >> 4;
        this->mapper += (this->header[8] & ALF_LOW_NIBBLE) << 8;
    }
    else if(this->version == 1){
        this->prgRamSize = this->header[8];
    }
}

void NesRomParser::parseInesFlag9(){
    if(this->version == 2){
        this->prgSize += (this->header[9] && ALF_LOW_NIBBLE) << 8;
        this->chrSize += (this->header[9] && ALF_HIGH_NIBBLE) << 4;
    }
    else if(this->version == 1){
        this->tvSystem = ALF_GET_BIT(this->header[9], 0);
    }
}

void NesRomParser::parseInesFlag10(){
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

void NesRomParser::parseInesFlag11(){
    if(this->version == 2){
        this->chrRamBatteryBacked = (ALF_HIGH_NIBBLE & this->header[11])>>4;
        this->chrRamNotBatteryBacked = (ALF_LOW_NIBBLE & this->header[11]);
    }
}

void NesRomParser::parseInesFlag12(){
    if(this->version == 2){
        this->pal = ALF_GET_BIT(this->header[12], 0);
        this->dual = ALF_GET_BIT(this->header[12], 1);

        this->tvSystem = this->pal;
    }
}

void NesRomParser::parseInesFlag13(){
    if(this->version == 2){
        this->chrRamBatteryBacked = (ALF_HIGH_NIBBLE & this->header[11])>>4;
        this->chrRamNotBatteryBacked = (ALF_LOW_NIBBLE & this->header[11]);
    }
}

void NesRomParser::parseInesFlag14(){
    if(this->version == 2){
        this->misc = ALF_GET_BIT(this->header[14], 1) | ALF_GET_BIT(this->header[14], 0);
    }
}

void NesRomParser::parseInesFlag15(){
    // void
}


int NesRomParser::getPrgPages(){
    return this->prgSize;
}
int NesRomParser::getChrPages(){
    return this->chrSize;
}
int NesRomParser::getPrgSize(){
    return this->prgSize*16384;
}
int NesRomParser::getChrSize(){
    return this->chrSize*8192;
}

bool NesRomParser::hasMirroring(){
    return this->mirroring;
}
bool NesRomParser::hasBattery(){
    return this->battery;
}
bool NesRomParser::hasTrainer(){
    return this->trainer;
}
bool NesRomParser::isIgnoreMirroring(){
    return this->ignoreMirroring;
}

int NesRomParser::getMapper(){
    return this->mapper;
}
int NesRomParser::getSubMapper(){
    return this->submapper;
}

bool NesRomParser::isVs(){
    return this->vsUnisystem;
}
bool NesRomParser::isPC10(){
    return this->pc10;
}

char NesRomParser::getPrgRamSize(){
    return this->prgRamSize;
}
bool NesRomParser::getTvSystem(){
    return this->tvSystem;
}
bool NesRomParser::isPal(){
    return this->pal;
}
bool NesRomParser::isDual(){
    return this->dual;
}
bool NesRomParser::isPrgRamPresent(){
    return this->prgRamPresent;
}
bool NesRomParser::hasBusConflicts(){
    return this->busConflicts;
}

char NesRomParser::getBatteryBacked(){
    return this->batteryBacked;
}
char NesRomParser::getNotBatteryBacked(){
    return this->notBatteryBacked;
}

char NesRomParser::getChrRamBatteryBacked(){
    return this->chrRamBatteryBacked;
}
char NesRomParser::getChrRamNotBatteryBacked(){
    return this->chrRamNotBatteryBacked;
}

char NesRomParser::getVsPPU(){
    return this->vsPPU;
}
char NesRomParser::getVsMode(){
    return this->vsMode;
}
char NesRomParser::getMisc(){
    return this->misc;
}

char NesRomParser::getVersion(){
    return this->version;
}
