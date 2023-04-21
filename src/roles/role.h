#ifndef ROLE_H
#define ROLE_H

#include "src/behaviors/behavior.h"

class Role : public Behavior
{
public:
    using Behavior::Behavior;
    void run();
};

#endif // ROLE_H
