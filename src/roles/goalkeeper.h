#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "src/roles/roles.h"

class Goalkeeper : public Roles
{
public:
    using Roles::Roles;
    void run(int8_t a, States* state);
};

#endif // GOALKEEPER_H
