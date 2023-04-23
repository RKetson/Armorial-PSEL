#include "dribbler.h"
#include <QtMath>
#include <QDebug>
#include "src/utils/utils.h"

#define ang_pp (11 * M_PI / 180)

//OBS: Implementar desvio para angulo específico, em vez de 180º ou 0º

// a =  1 -> Robô desvia indo pra esquerda
// a = -1 -> Robô desvia indo pra direita
bool Dribbler::run(int8_t a, QVector2D obstacle, float radius)
{
    Player* dribbler = getPlayer();

    qDebug() << "*************************************";
    QVector2D PO(obstacle - dribbler->getPosition());
    float ang = Utils::getAngle(obstacle, dribbler->getPosition());
    qDebug() << "Vetor: " << PO << "Angulo: " << ang;

    //Obs: Alterar condição de desvio para assim que o vetor PP esteja com uma diferença maior
    // do que 45º do vetor PB

    bool traveled = (a > 0 ? dribbler->getPosition().x() < obstacle.x() : dribbler->getPosition().x() > obstacle.x());
    bool ang_final = (a < 0 ? abs(ang) < (M_PI / 12) : (ang > 0 ? ang > (M_PI - M_PI/12) : ang < (-M_PI + M_PI/12)));

    qDebug() << traveled << a << ang_final << (PO.distanceToPoint(zero) < radius * 0.8);
    qDebug() << (ang > (M_PI*(1 - (1/12))));
    qDebug() << (M_PI - (M_PI/12));
    if(traveled && ang_final && (PO.distanceToPoint(zero) < radius * 0.8)){
        qDebug() << "Retornou";
        qDebug() << "*************************************";
        qDebug() << dribbler->getPosition();
        return true;
    }
    else if(ang >= 0){
        go(dribbler, obstacle + QVector2D(qCos(ang + a*ang_pp), qSin(ang + a*ang_pp)) * radius * 0.6);
    }
    else{
        go(dribbler, obstacle + QVector2D(qCos(ang - a*ang_pp), qSin(ang - a*ang_pp)) * radius * 0.6);
    }
    qDebug() << "*************************************";
    return false;
}
