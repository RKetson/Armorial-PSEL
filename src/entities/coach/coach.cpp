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
#include <QDebug>

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

void Coach::runCoach() {
    // Here you can control the robots freely.
    // Remember that the getPlayer(color, id) function can return a std::nullopt object, so
    // be careful when you use it (remember to only use ids from 0-2 and the BLUE and YELLOW
    // defines).

    // Example 1: here we get the ball position and set the BLUE and YELLOW player 0 to follow it

    //QVector2D position(0,0);
    QVector2D goalPosition = getWorldMap()->theirGoalCenter();
    QVector2D ballPosition = getWorldMap()->ballPosition();
    //QVector2D distanceGoal = (goalPosition - ballPosition);

    //float distancePlayerGoal = (distanceGoal - getPlayer(YELLOW, 0).value()->getPosition()).distanceToPoint(zero);

    float radius = getWorldMap()->centerRadius();
    float cordBall[2] = {getWorldMap()->ballPosition().x(), getWorldMap()->ballPosition().y()};
    float width = getWorldMap()->width();

    float difDist = width - abs(getWorldMap()->minY() - cordBall[1]);

    if(!getWorldMap()->playingLeftSide()){
        //if(cordBall[0] - getPlayer(YELLOW, 0).value()->getPosition().x() < 0.8 * radius){
         //   getPlayer(YELLOW, 0).value()->goTo(ballPosition);
        //}
        if(cordBall[0] < getPlayer(YELLOW, 0).value()->getPosition().x()){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition);
        }else if(difDist > width/2 + radius){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, -radius));
        }else if(difDist < width/2 - radius){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, radius));
        }else getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, 0.0));




        /*if(cordBall[1] < radius * 0.7){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, 0.0));
        }
        else if(abs(cordBall[1] - getWorldMap()->minY()) >= abs(cordBall[1] - getWorldMap()->maxY())){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, -radius));
        }else{
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(radius, radius));
        }
        */
    }else{
        if(goalPosition.distanceToPoint(ballPosition) < getWorldMap()->theirGoalLeftPost().distanceToPoint(ballPosition) || goalPosition.distanceToPoint(ballPosition) < getWorldMap()->theirGoalRightPost().distanceToPoint(ballPosition   )){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(-radius, 0.0));
        }
        else if(abs(cordBall[1] - getWorldMap()->minY()) >= abs(cordBall[1] - getWorldMap()->maxY())){
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(-radius, -radius));
        }else{
            getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(-radius, radius));
        }
    }
    //float position[2];

    //(abs(cordBall[1] - getWorldMap()->minY()) >= abs(cordBall[1] - getWorldMap()->maxY())) ? position[1] = (cordBall[1] - radius) : position[1] = (cordBall[1] + radius);

    //float distancePlayerGoal = (distanceGoal - getPlayer(YELLOW, 0).value()->getPosition()).distanceToPoint(zero);

    //position[0] = (cordBall[0] - radius * cordGoal[0] / abs(cordGoal[0]));

    //getPlayer(BLUE, 0).value()->goTo(ballPosition);
    //getPlayer(YELLOW, 0).value()->goTo(ballPosition + QVector2D(0.25,0.25 * cordGoal[0] / abs(cordGoal[0])));

    // Example 2: here we set the BLUE and YELLOW players 1 and 2 to rotate to the ball
    //getPlayer(BLUE, 1).value()->rotateTo(ballPosition);
    //getPlayer(BLUE, 2).value()->rotateTo(ballPosition);
    //getPlayer(YELLOW, 1).value()->rotateTo(ballPosition);
    //getPlayer(YELLOW, 2).value()->rotateTo(ballPosition);
}
