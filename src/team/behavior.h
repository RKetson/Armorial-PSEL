#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "src/entities/player/player.h"
#include "src/entities/worldmap/worldmap.h"
#include <optional>

class Behavior
{
public:
    Behavior(Player* player, WorldMap* wp);

    void run();
    WorldMap* getWorldMap();
    Player* getPlayer();

protected:
    void go(Player* player, QVector2D targetPosition);
    void rotate(Player* player, QVector2D targetPosition);
    void rotate(Player* player, float orientation);

private:
    Player* _player;
    WorldMap* _wp;
};

#endif // BEHAVIOR_H
