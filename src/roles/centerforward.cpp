#include "centerforward.h"

void CenterForward::run(int8_t a){

    WorldMap* wp = getWorldMap();
    QVector2D def_line = zero;
    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();

    if((ball.x() * a >= -(wp->maxX() - radius*1.5)) && (ball.x() * a <= zero.x()))
        Chaser(getPlayer(), wp).run(a);
    else
        Predictor(getPlayer(), wp).run(a, def_line.x(), radius * 1.5);

}
