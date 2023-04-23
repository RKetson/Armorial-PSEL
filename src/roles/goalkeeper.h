#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "src/roles/roles.h"

class Goalkeeper : public Roles
{
public:
    using Roles::Roles;
    void run(int8_t a);
};

#endif // GOALKEEPER_H
