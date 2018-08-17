#ifndef PRGROM_H
#define PRGROM_H

#include "abstractdatarom.h"

#define PRG_ROM_SIZE 16384

class PRGRom: public AbstractDataRom{
public:
    PRGRom(int pages, const char *prgRom);
    ~PRGRom();

private:
};

#endif // PRGROM_H
