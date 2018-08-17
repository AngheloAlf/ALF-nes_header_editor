#include "chrrom.h"

CHRRom::CHRRom(int pages, const char *chrRom) : AbstractDataRom(pages, chrRom, CHR_ROM_SIZE){

}

CHRRom::~CHRRom(){

}
