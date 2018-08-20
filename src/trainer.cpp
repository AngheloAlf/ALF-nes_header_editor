#include "trainer.h"
#include <stdlib.h>
#include <string.h>

Trainer::Trainer(const char *trainer){
    if(trainer != NULL){
        this->trainer = (char *)malloc(sizeof(char) * TRAINER_SIZE);
        memcpy(this->trainer, trainer, TRAINER_SIZE);
    }
    else{
        this->trainer = NULL;
    }
}

Trainer::~Trainer(){
    if(trainer != NULL){
        free(this->trainer);
    }
}

bool Trainer::hasTrainer(){
    return trainer != NULL;
}

void Trainer::setTrainer(const char *trainer){
    if(trainer == NULL){
        free(this->trainer);
        this->trainer = NULL;
    }
    else{
        if(this->trainer == NULL){
            this->trainer = (char *)malloc(sizeof(char) * TRAINER_SIZE);
        }
        memcpy(this->trainer, trainer, TRAINER_SIZE);
    }
}

const char* Trainer::getTrainer(){
    return trainer;
}
