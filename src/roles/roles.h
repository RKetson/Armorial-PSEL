#ifndef ROLES_H
#define ROLES_H

#include "src/behaviors/dribbler.h"
#include "src/behaviors/predictor.h"
#include "src/behaviors/chaser.h"
#include "src/utils/utils.h"
#include <math.h>

class Roles : public Behavior
{

public:

    using Behavior::Behavior;
    void run(int8_t a, States* state);
    void setListPlayers(const QMap<bool, QList<Player*>>& Players);

protected:
    QMap<bool, QList<Player*>> _players;
};

#endif // ROLES_H
