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

    qDebug() << "*************************************";
    QVector2D PO(obstacle - dribbler);
    float ang_op = Utils::getAngle(obstacle, dribbler);
    qDebug() << "Vetor: " << PO << "Angulo: " << ang_op;

    float ang_po = Utils::getAngle(dribbler, obstacle);
    float ang_pb = Utils::getAngle(dribbler, QVector2D(getWorldMap()->ballPosition().x() + step, getWorldMap()->ballPosition().y()));
    if(!(ang_po < ang_pb + M_PI/3 && ang_po > ang_pb - M_PI/3)){
        qDebug() << "Retornou";
        qDebug() << "*************************************";
        qDebug() << dribbler;
        return true;
    }
    else if(ang_op >= 0){
        go(getPlayer(), obstacle + QVector2D(qCos(ang_op + a*ang_pp), qSin(ang_op + a*ang_pp)) * radius * 0.6);
    }
    else{
        go(getPlayer(), obstacle + QVector2D(qCos(ang_op - a*ang_pp), qSin(ang_op - a*ang_pp)) * radius * 0.6);
    }
    qDebug() << "*************************************";
    return false;
}
