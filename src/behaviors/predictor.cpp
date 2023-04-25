#include "predictor.h"
#include <QDebug>

void Predictor::run(int8_t a, float linha_defesa, float posRobo, States* state)
{

    WorldMap* wp = getWorldMap();
    Player* predictor = getPlayer();

    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();

    //Máquina de estado para chutar a bola
    switch(state->ST_P){

        //Vai atrás da bola
        case STP_Search: {
            float frac = (wp->maxX() - posRobo) * a / predictor->getPosition().x();
            //qDebug() << "Search Predictor: " << frac;
            if(a * ball.x() > linha_defesa)
                state->ST_P = STP_Ajust;
            else if(!(frac > 0.8 && frac < 1.2)) go(predictor, QVector2D((wp->maxX() - posRobo) * a, 0));
            else state->ST_P = STP_Rotate;
        break;
        }

        //Rotacionar o robô em direção da bola
        case STP_Rotate:{
            rotate(predictor, ball);
            if(a * ball.x() > linha_defesa) state->ST_P = STP_Search;
        break;
        }

        //Ajusta a posição do jogador antes do chute
        case STP_Ajust: {
            go(predictor, ball + QVector2D(a * radius, 0));
            if(a * predictor->getPosition().x() > a * (ball.x() + radius * 0.8)) state->ST_P = STP_Shoot;
        break;
        }

        //Chutar a bola
        case STP_Shoot: {
            go(predictor, ball);
            if(a * ball.x() < linha_defesa) state->ST_P = STP_Search;
        break;
        }
    }

}
