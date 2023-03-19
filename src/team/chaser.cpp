#include "chaser.h"
#include <QtMath>
#include <QDebug>

void Chaser::run(){

    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Rotate, ST_Goal, ST_Back
    } States;

    static States state = ST_Search;

    qDebug() << state;

    int a;
    WorldMap* wp = getWorldMap();
    Player* chaser = getPlayer();

    // Indica qual lado do jogo estamos jogando
    wp->playingLeftSide() ? a = -1 : a = 1;

    QVector2D ball = wp->ballPosition();
    QVector2D zero(0,0);

    float width_goal = wp->goalWidth();
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

            float player_y = chaser->getPosition().y();
            if((abs(player_y) < width_goal) && !(abs(player_y) < 0.06)){
                go(chaser, ball - dir_Goal * radius * 0.6);
            }else state = ST_Rotate;

        break;
        }

        //Rotacionar o jogador em direção da bola
        case ST_Rotate: {

            float chaser_ori = tan(chaser->getOrientation());
            float pb_ori = tan(dist_PB[1] / dist_PB[0]);

            if(abs(chaser_ori) <= abs(pb_ori) * 1.2)
                state = ST_Goal;
            else rotate(chaser, ball);
        break;
        }

        //Chuta a bola
        case ST_Goal: {

            go(chaser, ball);
            QVector2D chaserPos(chaser->getPosition());
            qDebug() << (-a * chaserPos.x() > -a * wp->theirGoalCenter().x());
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
