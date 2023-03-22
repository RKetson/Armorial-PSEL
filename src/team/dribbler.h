#ifndef DRIBBLER_H
#define DRIBBLER_H

#include "behavior.h"

class Dribbler : public Behavior
{
public:
    using Behavior::Behavior;
    void run(uint8_t a);
};

#endif // DRIBBLER_H
