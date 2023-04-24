#include "dribbler.h"
#include <QtMath>
#include <QDebug>
#include "src/utils/utils.h"

#define ang_pp (11 * M_PI / 180)

// a =  1 -> Robô desvia indo pra esquerda
// a = -1 -> Robô desvia indo pra direita
bool Dribbler::run(int8_t a, QVector2D obstacle, float radius, float step)
{
    QVector2D dribbler = getPlayer()->getPosition();
    QVector2D ball = getWorldMap()->ballPosition();

    float ang_op = Utils::getAngle(obstacle, dribbler);
    float ang_po = Utils::getAngle(dribbler, obstacle);
    float ang_pb = Utils::getAngle(dribbler, QVector2D(ball.x() + step, ball.y()));

    int8_t mult = pow(-1, (dribbler.x() * a < obstacle.x() * a));
    if(!(mult * ang_po < mult * (ang_pb + M_PI/4) && mult * ang_po > mult * (ang_pb - M_PI/4))){
        return true;
    }
    else if(ang_op >= 0){
        go(getPlayer(), obstacle + QVector2D(qCos(ang_op + a*ang_pp), qSin(ang_op + a*ang_pp)) * radius * 0.6);
    }
    else{
        go(getPlayer(), obstacle + QVector2D(qCos(ang_op - a*ang_pp), qSin(ang_op - a*ang_pp)) * radius * 0.6);
    }
    return false;
}
