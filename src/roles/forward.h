#ifndef FORWARD_H
#define FORWARD_H

#include "src/roles/roles.h"

class Forward : public Roles
{

public:
    using Roles::Roles;
    void run(int8_t a, Roles::States* state);
};

#endif // FORWARD_H
