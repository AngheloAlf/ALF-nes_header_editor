#ifndef NESROMPARSER_H
#define NESROMPARSER_H

#include <string>

class NesRomParser
{
public:
    NesRomParser(std::string nesRomFullPath);
    ~NesRomParser();

    char getVersion();

    // Flags 4 & 5
    int getPrgPages();
    int getChrPages();
    int getPrgSize();
    int getPrgSize(unsigned int pages);
    int getChrSize();
    int getChrSize(unsigned int pages);

    // Flag 6
    bool hasMirroring();
    bool hasBattery();
    bool hasTrainer();
    bool isIgnoreMirroring();

    int getMapper();
    // Flag 8
    int getSubMapper();

    // Flag 7
    bool isVs();
    bool isPC10();

    // Flag 8 v1
    char getPrgRamSize(); // TODO: investigate

    // Flag 9 v1
    bool getTvSystem();

    // Flag 10 v1
    bool isPal();
    bool isDual();
    bool isPrgRamPresent();
    bool hasBusConflicts();

    // Flag 10 v2
    char getBatteryBacked();
    char getNotBatteryBacked();

    // Flag 11 v2
    char getChrRamBatteryBacked();
    char getChrRamNotBatteryBacked();

    // Flag 13 v2
    char getVsPPU();
    char getVsMode();

    // Flag 14 v2
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
