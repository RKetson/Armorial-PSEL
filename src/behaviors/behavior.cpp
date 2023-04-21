#include "behavior.h"

Behavior::Behavior(Player* player, WorldMap *wp)
    : _player(player), _wp(wp)
{
}

void Behavior::go(Player* player, QVector2D targetPosition){
    player->goTo(targetPosition);
}

void Behavior::rotate(Player* player, QVector2D targetPosition){
    player->rotateTo(targetPosition);
}

void Behavior::rotate(Player* player, float orientation){
    player->rotateTo(orientation);
}

WorldMap* Behavior::getWorldMap(){
    return _wp;
}

Player* Behavior::getPlayer(){
    return _player;
}

void Behavior::run(){

}
