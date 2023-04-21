#ifndef FORWARD_H
#define FORWARD_H

#include "src/behaviors/behavior.h"

class Forward : Behavior
{
public:
    using Behavior::Behavior;
    void run(int8_t a);
};

#endif // FORWARD_H
