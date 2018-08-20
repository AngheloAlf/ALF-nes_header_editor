#include "pc10.h"

#include <stdlib.h>
#include <string.h>

PC10::PC10(const char *pc10, const char *pc10Data, const char *pc10CounterOut){
    this->pc10Rom = NULL;
    this->pc10DataPRom = NULL;
    this->pc10CounterOutPRom = NULL;
    if(pc10){
        this->pc10Rom = (char *)malloc(sizeof(char) * PC10_ROM_SIZE);
        memcpy(this->pc10Rom, pc10, PC10_ROM_SIZE);
        if(pc10Data){
            this->pc10DataPRom = (char *)malloc(sizeof(char) * PC10_DATA_PROM_SIZE);
            memcpy(this->pc10DataPRom, pc10Data, PC10_DATA_PROM_SIZE);
            if(!pc10CounterOut){
                this->pc10CounterOutPRom = (char *)malloc(sizeof(char) * PC10_CO_PROM_SIZE);
                memcpy(this->pc10CounterOutPRom, COUNTER_OUT_PROM_DEFAULT, PC10_CO_PROM_SIZE);
            }
        }
        if(pc10CounterOut){
            this->pc10CounterOutPRom = (char *)malloc(sizeof(char) * PC10_CO_PROM_SIZE);
            memcpy(this->pc10CounterOutPRom, pc10CounterOut, PC10_CO_PROM_SIZE);
        }
    }
    
}

PC10::~PC10(){
    if(pc10Rom){
        free(pc10Rom);
    }
    if(pc10DataPRom){
        free(pc10DataPRom);
    }
    if(pc10CounterOutPRom){
        free(pc10CounterOutPRom);
    }
}
