#ifndef CENTERFORWARD_H
#define CENTERFORWARD_H

#include "src/roles/roles.h"

class CenterForward : public Roles
{
public:
    using Roles::Roles;
    void run(int8_t a);
};

#endif // CENTERFORWARD_H
