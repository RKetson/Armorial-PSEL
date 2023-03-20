#include "chaser.h"
#include <QtMath>
#include <QDebug>

void Chaser::run(){

    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Rotate, ST_Goal, ST_Back
    } States;

    static States state = ST_Search;

    int a;
    WorldMap* wp = getWorldMap();
    Player* chaser = getPlayer();

    // Indica qual lado do jogo estamos jogando
    wp->playingLeftSide() ? a = -1 : a = 1;

    QVector2D ball = wp->ballPosition();
    QVector2D zero(0,0);

    float width = wp->width();
    //Distância da parte superior até a bola
    float distY = width/2 - ball.y();
    float radius = wp->centerRadius();
    QVector2D dir_Goal = (wp->theirGoalCenter() - ball) / (wp->theirGoalCenter() - ball).distanceToPoint(zero);

    //Distância da bola até o player
    float dist_PB[2] = {chaser->getPosition().x() - ball.x(), chaser->getPosition().y() - ball.y()};

    //Máquina de estado para chutar a bola
    switch(state){

        //Vai atrás da bola
        case ST_Search: {

            if(distY > width/2) go(chaser, ball + QVector2D(a * radius, radius));
            else if(distY < width/2) go(chaser, ball + QVector2D(a * radius, -radius));
            else{
                if(width/2 - chaser->getPosition().y() > width/2) go(chaser, ball + QVector2D(a * radius, -radius));
                else go(chaser, ball + QVector2D(a * radius, radius));
            }

            if(((dist_PB[0] * a > radius * 0.8) && (dist_PB[0] * a < radius * 1.2)) && (abs(dist_PB[1]) < radius * 1.2)) state = ST_Ajust;

        break;
        }

        //Ajusta a posição do jogador antes do chute
        case ST_Ajust: {

            QVector2D ajust_Pos(chaser->getPosition() - ball);
            if(ajust_Pos.distanceToPoint(zero) > radius * 0.6 && ajust_Pos.distanceToPoint(zero) < radius * 0.8){
                float frac = -(dir_Goal.y() * radius * 0.7 / qSqrt(2)) / ajust_Pos.y();
                qDebug() << "Ajust Chaser: " << frac;
                if((frac < 0.8 && frac > 0.6) || (1/frac < 0.8 && 1/frac > 0.6) || (abs(chaser->getPosition().y()) < 0.03 && abs(ball.y()) < 0.03)) state = ST_Goal;
                else go(chaser, ball - dir_Goal * radius * 0.7);
            }else go(chaser, ball - dir_Goal * radius * 0.7);

        break;
        }

        //Rotacionar o jogador em direção da bola
        case ST_Rotate: {

            float chaser_ori = abs(tan(chaser->getOrientation()));
            float pb_ori = abs(tan(dist_PB[1] / dist_PB[0]));
            if(pb_ori / chaser_ori < 1.2 && pb_ori / chaser_ori > 0.8)
                state = ST_Goal;
            else rotate(chaser, ball);
        break;
        }

        //Chuta a bola
        case ST_Goal: {

            go(chaser, ball);
            QVector2D chaserPos(chaser->getPosition());
            if((ball - chaserPos).distanceToPoint(zero) > 2 * radius || -a * chaserPos.x() > -a * wp->theirGoalCenter().x())
                state = ST_Back;

        break;
        }

        //Volta pra o lado campo após chutar a bola
        case ST_Back: {

            go(chaser, QVector2D(a * 1.2 * radius, 0));

            if(a * chaser->getPosition().x() > radius)
                state = ST_Search;

        break;
        }
    }

}
