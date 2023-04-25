#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "behavior.h"

class Predictor: public Behavior
{

public:
    using Behavior::Behavior;
    void run(int8_t a, float linha_defesa, float posRobo, States* state);
};

#endif // PREDICTOR_H
