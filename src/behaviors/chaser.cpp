#include "chaser.h"
#include <QtMath>
#include "src/utils/utils.h"

void Chaser::run(int8_t a){

    typedef enum{
        ST_Ajust = 0, ST_Rotate, ST_Goal, ST_Back
    } States;

    static States state = ST_Ajust;

    WorldMap* wp = getWorldMap();
    Player* chaser = getPlayer();

    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();

    QVector2D dir_Goal = (wp->theirGoalCenter() - ball).normalized();

    int id = chaser->getPlayerId();

    std::cout << "Estado: " << state << " | Jogador: " << id << " \n";


    //Máquina de estado para chutar a bola
    switch(state){

        //Ajusta a posição do jogador antes do chute
        case ST_Ajust: {
            float const_mult;
            QVector2D ajust_Pos(chaser->getPosition() - ball);
            abs((ball - dir_Goal * radius * 1.3).y()) > (wp->maxY() - abs(ball.y())) ? const_mult = 0.7 : const_mult = 1.6;

            if(ajust_Pos.distanceToPoint(zero) < radius * (const_mult + 0.1)){
                float ang_pb = Utils::getAngle(chaser->getPosition(), ball);
                float ang_dist = Utils::getAngle(chaser->getPosition(), wp->theirGoalCenter());

                if(ang_pb < ang_dist + M_PI/36 && ang_pb > ang_dist - M_PI/36) state = ST_Rotate;
                else{
                    go(chaser, (ball - dir_Goal * radius * const_mult));
                }
            }else{
                go(chaser, ball - dir_Goal * radius * const_mult);
            }

        break;
        }

        //Rotacionar o jogador em direção da bola
        case ST_Rotate: {

            //float chaser_ori = abs(tan(chaser->getOrientation()));
            float chaser_ori = chaser->getOrientation();
            float pb_ori = Utils::getAngle(chaser->getPosition(), ball);

            //float pb_ori = abs(tan(dist_PB[1] / dist_PB[0]));
            if(chaser_ori < pb_ori + M_PI/36 && chaser_ori > pb_ori - M_PI/36)
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

            go(chaser, QVector2D(a * radius, 0));

            if(a * chaser->getPosition().x() > radius * 0.8)
                state = ST_Ajust;

        break;
        }
    }

}
