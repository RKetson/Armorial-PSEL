#ifndef CHASER_H
#define CHASER_H

#include "behavior.h"

class Chaser : public Behavior
{
public:
    using Behavior::Behavior;
    void run();
};

#endif // CHASER_H
