#include "roles.h"

void Roles::setListPlayers(const QMap<bool, QList<Player*>>& Players){
    _players = Players;
}
