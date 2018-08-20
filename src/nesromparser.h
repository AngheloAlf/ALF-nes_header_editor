#ifndef NESROMPARSER_H
#define NESROMPARSER_H

#include <string>
#include "nesromheader.h"
#include "trainer.h"
#include "prgrom.h"
#include "chrrom.h"
#include "pc10.h"

class NesRomParser{
public:
    NesRomParser(std::string nesRomFullPath);
    ~NesRomParser();

    NesRomHeader *getHeader();

private:
    void parseRom();

    void parseRestRom();

    std::string fullPath;
    int fileSize = 0;
    /// The full rom without header
    char *fullRom;

    bool error = false;

    NesRomHeader *header;

    // Trainer
    // char *trainerRom = NULL;
    Trainer *trainerRom;


    // Prg and Chr Rom
    // char *prgRom;
    // char *chrRom = NULL;
    PRGRom *prgRom;
    CHRRom *chrRom;


    // PC10 Rom
    // char *pc10Rom = NULL;
    // char *pc10DataPRom = NULL;
    // char *pc10CounterOutPRom = NULL;
    PC10 *pc10Rom;

    char *title = NULL;
};

#endif // NESROMPARSER_H
