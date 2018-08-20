#ifndef PC10_H
#define PC10_H

#define PC10_ROM_SIZE 8192
#define PC10_DATA_PROM_SIZE 16
#define PC10_CO_PROM_SIZE 16
#define COUNTER_OUT_PROM_DEFAULT "\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\xFF\xFF\xFF\xFF"

class PC10{
public:
    PC10(const char *pc10, const char *pc10Data, const char *pc10CounterOut);
    ~PC10();
private:

    char *pc10Rom;
    char *pc10DataPRom;
    char *pc10CounterOutPRom;
};

#endif // PC10_H
