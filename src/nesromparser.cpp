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
    // fprintf(stderr, "%s\n", this->fullPath.c_str());

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

    char header[16];
    if(!nesFile.read(header, 16)){
        // TODO: throw exception
        this->error = true;
        free(this->header);
        return;
    }
    /*for(int i  = 0; i< 16; i++){
        fprintf(stderr, "%i 0x%x\n", i, this->header[i]);
    }*/
    this->fullRom = (char *)malloc(sizeof(char)*(this->fileSize-16));
    if(!nesFile.read(this->fullRom, this->fileSize-16)){
        // TODO: throw exception
        this->error = true;
        free(this->header);
        return;
    }
    nesFile.close();
    this->header = new NesRomHeader(header, this->fileSize);
    this->parseRestRom();
}

void NesRomParser::parseRestRom(){
    int size = this->fileSize - 16;
    int reader = 0;
    int aux_size;

    if(header->hasTrainer()){
        trainerRom = new Trainer(&fullRom[reader]);
        // trainerRom = (char *)malloc(sizeof(char) * TRAINER_SIZE);
        // memcpy(trainerRom, &fullRom[reader], TRAINER_SIZE);
        size -= TRAINER_SIZE;
        reader += TRAINER_SIZE;
        if(size < 0){
            // Throw exception
            error = true;
            return;
        }
    }
    else{
        trainerRom = new Trainer(NULL);
    }

    aux_size = header->getPrgSize();
    // prgRom = (char *)malloc(sizeof(char) * aux_size);
    // memcpy(prgRom, &fullRom[reader], aux_size);
    prgRom = new PRGRom(aux_size, &fullRom[reader]);
    size -= aux_size;
    reader += aux_size;
    if(size < 0){
        // Throw exception
        error = true;
        return;
    }

    aux_size = header->getChrSize();
    if(aux_size > 0){
        // chrRom = (char *)malloc(sizeof(char) * aux_size);
        // memcpy(chrRom, &fullRom[reader], aux_size);
        chrRom = new CHRRom(aux_size, &fullRom[reader]);
        size -= aux_size;
        reader += aux_size;
        if(size < 0){
            // Throw exception
            error = true;
            return;
        }
    }
    else{
        chrRom = new CHRRom(0, NULL);
    }

    if(header->isPC10()){
        aux_size = PC10_ROM_SIZE;
        const char *pc10 = &fullRom[reader];
        const char *pc10Data = NULL;
        const char *pc10CO = NULL;

        // pc10Rom = (char *)malloc(sizeof(char) * aux_size);
        // memcpy(pc10Rom, &fullRom[reader], aux_size);
        size -= aux_size;
        reader += aux_size;
        if(size < 0){
            // Throw exception
            error = true;
            return;
        }
        if(size >= 32){ // Maybe it has the PlayChoice PROM
            if(size == 32 || size == 159 || size == 160){ // There's the PlayChoice PROM or (PlayChoice PROM + title)
                aux_size = PC10_DATA_PROM_SIZE;
                // pc10DataPRom = (char *)malloc(sizeof(char)*aux_size);
                // memcpy(pc10DataPRom, &fullRom[reader], aux_size);
                pc10Data = &fullRom[reader];
                size -= aux_size;
                reader += aux_size;

                aux_size = PC10_CO_PROM_SIZE;
                // pc10CounterOutPRom = (char *)malloc(sizeof(char)*aux_size);
                // memcpy(pc10CounterOutPRom, &fullRom[reader], aux_size);
                pc10CO = &fullRom[reader];
                size -= aux_size;
                reader += aux_size;
            }
        }
        pc10Rom = new PC10(pc10, pc10Data, pc10CO);
    }
    else{
        pc10Rom = new PC10(NULL, NULL, NULL);
    }

    if(size > 0){
        aux_size = size;
        title = (char *)malloc(sizeof(char) * aux_size);
        memcpy(title, &fullRom[reader], aux_size);
        size -= aux_size;
        reader += aux_size;
    }
}


NesRomHeader *NesRomParser::getHeader(){
    return this->header;
}
