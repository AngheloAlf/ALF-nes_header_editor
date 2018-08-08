#ifndef NESROMPARSER_H
#define NESROMPARSER_H

#include <string>

class NesRomParser
{
public:
    NesRomParser(std::string nesRomFullPath);
    ~NesRomParser();

    int getPrgPages();
    int getChrPages();
    int getPrgSize();
    int getChrSize();
    bool hasMirroring();
    bool hasBattery();
    bool hasTrainer();
    bool isIgnoreMirroring();
    int getMapper();
    int getSubMapper();
    bool isVs();
    bool isPC10();
    char getPrgRamSize();
    bool getTvSystem();
    bool isPal();
    bool isDual();
    bool isPrgRamPresent();
    bool hasBusConflicts();
    char getBatteryBacked();
    char getNotBatteryBacked();
    char getChrRamBatteryBacked();
    char getChrRamNotBatteryBacked();
    char getVsPPU();
    char getVsMode();
    char getMisc();

private:
    void parseRom();
    void parseHeader();
    void parseINES();
    void parseInesFlag6();
    void parseInesFlag7();
    void parseInesFlag8();
    void parseInesFlag9();
    void parseInesFlag10();
    void parseInesFlag11();
    void parseInesFlag12();
    void parseInesFlag13();
    void parseInesFlag14();
    void parseInesFlag15();

    std::string fullPath;
    int fileSize = 0;

    bool error = false;

    char *header;
    char *headerID;

    char version = 0;

    int prgSize = 0;
    int chrSize = 0;

    bool mirroring;
    bool battery;
    bool trainer;
    bool ignoreMirroring;

    int mapper;
    int submapper = 0;

    bool vsUnisystem = 0;
    bool pc10 = 0;

    // v1
    char prgRamSize = 0;
    bool tvSystem = false;
    bool pal = false;
    bool dual = false;
    bool prgRamPresent = false;
    bool busConflicts = false;

    // Ram size
    char batteryBacked = 0;
    char notBatteryBacked = 0;

    char chrRamBatteryBacked = 0;
    char chrRamNotBatteryBacked = 0;

    // Vs.
    char vsPPU = 0;
    char vsMode = 0;

    char misc = 0;

    // char *title;
};

#endif // NESROMPARSER_H
