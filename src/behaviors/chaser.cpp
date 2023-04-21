#include "chaser.h"
#include <QtMath>
#include <QDebug>

#define ang_pp (11 * M_PI / 180)

void Chaser::run(int8_t a){

    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Rotate, ST_Goal, ST_Back
    } States;

    static States state_c = ST_Search;

    WorldMap* wp = getWorldMap();
    Player* chaser = getPlayer();

    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();

    QVector2D dir_Goal = (wp->theirGoalCenter() - ball) / (wp->theirGoalCenter() - ball).distanceToPoint(zero);

    //Distância da bola até o player
    float dist_PB[2] = {chaser->getPosition().x() - ball.x(), chaser->getPosition().y() - ball.y()};

    //Máquina de estado para chutar a bola
    switch(state_c){

        //Vai atrás da bola
        case ST_Search: {

            QVector2D PB(ball - chaser->getPosition());
            float ang = qAtan(PB.y()/PB.x());
            qDebug() << "Vetor: " << PB << "Angulo: " << ang;
            bool behind = chaser->getPosition().x() * a > ball.x() * a;
            qDebug() << behind;
            if(behind && abs(ang) < (M_PI / 12) && PB.distanceToPoint(zero) < radius * 1.2)
                state_c = ST_Ajust;
            else if((ang >= 0 && !behind) || (ang < 0 && behind)){
                go(chaser, ball + QVector2D(qCos(ang + ang_pp) * qPow(-1, behind), qSin(ang + ang_pp)) * radius);
                qDebug() << "Aqui miseria";
            }
            else if((ang < 0 && !behind) || (ang >= 0 && behind)){
                go(chaser, ball + QVector2D(qCos(ang - ang_pp) * qPow(-1, behind), qSin(ang - ang_pp)) * radius);
                qDebug() << "Agora agui";
            }
        break;
        }

        //Ajusta a posição do jogador antes do chute
        case ST_Ajust: {

            QVector2D ajust_Pos(chaser->getPosition() - ball);
            if(ajust_Pos.distanceToPoint(zero) > radius * 0.6 && ajust_Pos.distanceToPoint(zero) < radius * 0.8){
                float frac = -(dir_Goal.y() * radius * 0.7 / qSqrt(2)) / ajust_Pos.y();
                qDebug() << "Ajust Chaser: " << frac;
                if((frac < 0.8 && frac > 0.6) || (1/frac < 0.8 && 1/frac > 0.6) || (abs(chaser->getPosition().y()) < 0.03 && abs(ball.y()) < 0.03)) state_c = ST_Goal;
                else go(chaser, ball - dir_Goal * radius * 0.7);
            }else go(chaser, ball - dir_Goal * radius * 0.7);

        break;
        }

        //Rotacionar o jogador em direção da bola
        case ST_Rotate: {

            float chaser_ori = abs(tan(chaser->getOrientation()));
            float pb_ori = abs(tan(dist_PB[1] / dist_PB[0]));
            if(pb_ori / chaser_ori < 1.2 && pb_ori / chaser_ori > 0.8)
                state_c = ST_Goal;
            else rotate(chaser, ball);
        break;
        }

        //Chuta a bola
        case ST_Goal: {

            go(chaser, ball);
            QVector2D chaserPos(chaser->getPosition());
            if(chaserPos.x() * a < ball.x() * a) state_c = ST_Search;
            else if((ball - chaserPos).distanceToPoint(zero) > 2 * radius || -a * chaserPos.x() > -a * wp->theirGoalCenter().x())
                state_c = ST_Back;

        break;
        }

        //Volta pra o lado campo após chutar a bola
        case ST_Back: {

            go(chaser, QVector2D(a * 1.2 * radius, 0));

            if(a * chaser->getPosition().x() > radius)
                state_c = ST_Search;

        break;
        }
    }

}
