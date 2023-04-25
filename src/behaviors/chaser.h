#ifndef CHASER_H
#define CHASER_H

#include "behavior.h"

class Chaser : public Behavior
{
public:
    using Behavior::Behavior;
    void run(int8_t a, States* state);
};

#endif // CHASER_H
