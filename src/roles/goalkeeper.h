#ifndef GOALKEEPER_H
#define GOALKEEPER_H

#include "src/behaviors/behavior.h"

class Goalkeeper : Behavior
{
public:
    using Behavior::Behavior;
    void run(int8_t a);
    void setListPlayers(const QMap<bool, QList<Player*>>& Players);
private:
    QMap<bool, QList<Player*>> _players;
};

#endif // GOALKEEPER_H
