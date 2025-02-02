#ifndef DRIBBLER_H
#define DRIBBLER_H

#include "behavior.h"

class Dribbler : public Behavior
{
public:
    using Behavior::Behavior;
    bool run(int8_t a, QVector2D obstacle, float radius, float step = 0);
};

#endif // DRIBBLER_H
