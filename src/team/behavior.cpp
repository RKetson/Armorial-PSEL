#include "behavior.h"

Behavior::Behavior(std::optional<Player*> player, WorldMap *wp)
    :_player(player), _wp(wp)
{
}

std::optional<Player*> Behavior::getPlayer(){
    return _player;
}

WorldMap* Behavior::getWorldMap(){
    return _wp;
}

void Behavior::run(){

}
