#include "behavior.h"

Behavior::Behavior(Player* player, WorldMap *wp)
    : _player(player), _wp(wp)
{
}

WorldMap* Behavior::getWorldMap(){
    return _wp;
}

Player* Behavior::getPlayer(){
    return _player;
}

void Behavior::run(){

}
