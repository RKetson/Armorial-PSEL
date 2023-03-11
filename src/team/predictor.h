#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "behavior.h"

class Predictor: public Behavior
{
public:
    using Behavior::Behavior;
    void run();

};

#endif // PREDICTOR_H
