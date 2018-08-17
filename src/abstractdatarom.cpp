#include "abstractdatarom.h"
#include <stdlib.h>
#include <string.h>

AbstractDataRom::AbstractDataRom(int pages, const char *rom, int pageSize){
    this->pages = pages;
    this->rom = (char **)malloc(sizeof(char *) * pages);
    for(int i = 0; i < pages; i++){
        this->rom[i] = (char *)malloc(sizeof(char) * pageSize);
        memcpy(this->rom[i], &rom[pageSize * i], pageSize);
    }
}

AbstractDataRom::~AbstractDataRom(){
    // TODO: this
}
