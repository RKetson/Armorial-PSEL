#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "src/entities/player/player.h"
#include "src/entities/worldmap/worldmap.h"
#include <optional>

class Behavior
{
public:
    Behavior(std::optional<Player*>, WorldMap* wp);

    std::optional<Player*> getPlayer();
    WorldMap* getWorldMap();
    void run();

private:
    std::optional<Player*> _player;
    WorldMap* _wp;
};

#endif // BEHAVIOR_H
