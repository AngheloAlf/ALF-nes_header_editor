#ifndef TRAINER_H
#define TRAINER_H

#define TRAINER_SIZE 512

class Trainer{
public:
    Trainer(const char *trainer);
    ~Trainer();
    bool hasTrainer();
    void setTrainer(const char *trainer);
    const char* getTrainer();

private:
    char *trainer;
};

#endif // TRAINER_H
