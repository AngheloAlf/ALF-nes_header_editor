#ifndef CHRROM_H
#define CHRROM_H

#include "abstractdatarom.h"

#define CHR_ROM_SIZE 8192

class CHRRom: public AbstractDataRom{
public:
    CHRRom(int pages, const char *prgRom);
    ~CHRRom();
};

#endif // CHRROM_H
