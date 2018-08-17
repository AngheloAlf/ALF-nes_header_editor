#ifndef ABSTRACTDATAROM_H
#define ABSTRACTDATAROM_H


class AbstractDataRom{
public:
    AbstractDataRom(int pages, const char *rom, int pageSize);
    ~AbstractDataRom();

protected:
    int pages;
    char **rom;
};

#endif // ABSTRACTDATAROM_H
