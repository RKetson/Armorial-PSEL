/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "coach.h"
#include "src/roles/goalkeeper.h"
#include "src/roles/centerforward.h"
#include "src/roles/forward.h"

#include "src/utils/utils.h"
#include <QDebug>
#include <QtMath>

Coach::Coach(const QMap<bool, QList<Player*>>& players, WorldMap* worldMap)
    : _players(players), _worldMap(worldMap)
{
    // Create QTimer and connects to the runCoach() slot
    _actuatorTimer = new QTimer(this);
    QObject::connect(_actuatorTimer, &QTimer::timeout, this, &Coach::runCoach);
    _actuatorTimer->start(COACH_ITERATION_INTERVAL_MS);
}

std::optional<Player*> Coach::getPlayer(const bool& isTeamBlue, const quint8& playerId) {
    // Get list of players
    QList<Player*> playersForColor = _players.value(isTeamBlue);

    // Iterate searching for playerId
    for(const auto& player : playersForColor) {
        if(player->getPlayerId() == playerId) {
            return player;
        }
    }

    // If could not found, just return std::nullopt (should trait later)
    return std::nullopt;
}

WorldMap* Coach::getWorldMap() {
    return _worldMap;
}

QMap<bool, QList<Player*>> Coach::getPlayers(){
    return _players;
}

void Coach::runCoach() {

    WorldMap *wp = getWorldMap();

    static Roles::States state_GK;
    static Roles::States state_CF;
    static Roles::States state_FW;

    int8_t a;
    // Indica qual lado do jogo estamos jogando
    wp->playingLeftSide() ? a = -1 : a = 1;

    Forward* jogador0 = new Forward(getPlayer(BLUE, 0).value(), wp);
    jogador0->setListPlayers(getPlayers());

    CenterForward* jogador1 = new CenterForward(getPlayer(BLUE, 1).value(), wp);
    jogador1->setListPlayers(getPlayers());

    Goalkeeper* jogador2 = new Goalkeeper(getPlayer(BLUE, 2).value(), wp);
    jogador2->setListPlayers(getPlayers());


    jogador0->run(a, &state_FW);
    jogador1->run(a, &state_CF);
    jogador2->run(a, &state_GK);

}
