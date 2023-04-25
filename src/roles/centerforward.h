#ifndef CENTERFORWARD_H
#define CENTERFORWARD_H

#include "src/roles/roles.h"

class CenterForward : public Roles
{
public:
    using Roles::Roles;
    void run(int8_t a, States* state);
};

#endif // CENTERFORWARD_H
