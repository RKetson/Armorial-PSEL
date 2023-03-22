#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "behavior.h"

class Predictor: public Behavior
{
public:
    using Behavior::Behavior;
    void run(uint8_t a);

};

#endif // PREDICTOR_H
