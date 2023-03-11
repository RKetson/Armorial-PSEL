#include "chaser.h"

void Chaser::run(){

    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Goal, ST_Back
    } States;

    static States state = ST_Search;

    int a;
    WorldMap* wp = getWorldMap();
    Player* chaser = getPlayer();
    // Indica qual lado do jogo estamos jogando
    wp->playingLeftSide() ? a = -1 : a = 1;

    QVector2D ball = wp->ballPosition();
    float width = wp->width();
    //Distância da parte superior até a bola
    float distY = width/2 - ball.y();
    float radius = wp->centerRadius();
    //Distância da bola até o player
    float dist_PB[2] = {chaser->getPosition().x() - ball.x(), chaser->getPosition().y() - ball.y()};
    //Máquina de estado para chutar a bola
    switch(state){
        //Verifica se o jogador está atrás da bola
//        case ST_Search: {

//            if(ball.x() > a*yellow->getPosition().x()) state = ST_Detour;
//            else state = ST_Ajust;

//        break;
//        }

        //Vai atrás da bola
        case ST_Search: {

            if(distY > width/2) chaser->goTo(ball + QVector2D(a * radius, radius));
            else if(distY < width/2) chaser->goTo(ball + QVector2D(a * radius, -radius));
            else{
                if(width/2 - chaser->getPosition().y() > width/2) chaser->goTo(ball + QVector2D(a * radius, -radius));
                else chaser->goTo(ball + QVector2D(a * radius, radius));
            }

            if(((dist_PB[0] * a > radius * 0.8) && (dist_PB[0] * a < radius * 1.2)) && (abs(dist_PB[1]) < radius * 1.2)) state = ST_Ajust;

        break;
        }

        //Ajusta a posição do jogador antes do chute
        case ST_Ajust: {

            float width_goal = wp->goalWidth();
            float player_y = abs(chaser->getPosition().y());

            if((player_y < width_goal) && !(player_y < 0.06))
                chaser->goTo(ball + QVector2D(a * radius, 0));
            else state = ST_Goal;

        break;
        }

        //Chuta a bola
        case ST_Goal: {

            chaser->goTo(ball);

            if((ball - chaser->getPosition()).distanceToPoint(chaser->getPosition()) > 3 * radius)
                state = ST_Back;

        break;
        }

        //Volta pra o lado campo após chutar a bola
        case ST_Back: {

            chaser->goTo(QVector2D(a * 1.2 * radius, 0));

            if(chaser->getPosition().x() > a * radius)
                state = ST_Search;

        break;
        }
    }

}
