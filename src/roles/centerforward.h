#ifndef CENTERFORWARD_H
#define CENTERFORWARD_H

#include "src/behaviors/behavior.h"
#include "src/behaviors/chaser.h"
#include "src/behaviors/predictor.h"

class CenterForward : Behavior
{
public:
    using Behavior::Behavior;
    void run(int8_t a);
};

#endif // CENTERFORWARD_H
