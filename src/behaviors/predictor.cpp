#include "predictor.h"
#include <QDebug>

void Predictor::run(int8_t a, float linha_defesa, float posRobo)
{

    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Rotate, ST_Shoot
    } States;

    static States state = ST_Search;

    WorldMap* wp = getWorldMap();
    Player* predictor = getPlayer();

    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();

    //Máquina de estado para chutar a bola
    switch(state){

        //Vai atrás da bola
        case ST_Search: {
            //Obs: Mudar lógica fazendo uso de frac para uso de ângulo
            float frac = (wp->maxX() - posRobo) * a / predictor->getPosition().x();
            qDebug() << "Search Predictor: " << frac;
            if(a * ball.x() > linha_defesa)
                state = ST_Ajust;
            else if(!(frac > 0.8 && frac < 1.2)) go(predictor, QVector2D((wp->maxX() - posRobo) * a, 0));
            else state = ST_Rotate;
        break;
        }

        //Rotacionar o robô em direção da bola
        case ST_Rotate:{
            rotate(predictor, ball);
            if(a * ball.x() > linha_defesa) state = ST_Search;
        break;
        }

        //Ajusta a posição do jogador antes do chute
        case ST_Ajust: {
            go(predictor, ball + QVector2D(a * radius, 0));
            if(a * predictor->getPosition().x() > a * (ball.x() + radius * 0.8)) state = ST_Shoot;
        break;
        }

        //Chutar a bola
        case ST_Shoot: {
            go(predictor, ball);
            if(a * ball.x() < linha_defesa) state = ST_Search;
        break;
        }
    }

}
