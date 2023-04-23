#include "goalkeeper.h"
#include <QDebug>

void Goalkeeper::run(int8_t a)
{
    typedef enum{
        ST_Search = 0, ST_Detour
    } States;

    static States state = ST_Search;

    WorldMap* wp = getWorldMap();
    QVector2D ball = wp->ballPosition();
    QVector2D def_line = zero;
    QVector2D gk = getPlayer()->getPosition();
    float radius = wp->centerRadius();

    static Player* detour_P;

    // obj_detour = 1  ->  Desvia de um jogador
    // obj_detour = 0  ->  Desvia da bola
    static bool obj_detour;

    static int8_t detour;

    qDebug() << detour;

    switch (state) {

        // Verifica se existe algum obstáculo e seleciona o behavior de acordo com sua posição
        case ST_Search:{

            if(ball.x() * a > def_line.x() * a){
                for(int i = 0; i <= 1; i++){
                    for(const auto& player : _players.value(i)){
                        if((player->isTeamBlue() != getPlayer()->isTeamBlue()) || (player->getPlayerId() != getPlayer()->getPlayerId())){
                            float ang_pp = Utils::getAngle(gk, player->getPosition());
                            float ang_pb = Utils::getAngle(gk, ball);
                            qDebug() << player->isTeamBlue() << player->getPlayerId() << ang_pp << ang_pb;
                            if((gk - player->getPosition()).distanceToPoint(zero) < wp->centerRadius() && (ang_pp < ang_pb + M_PI / 4 && ang_pp > ang_pb - M_PI / 4)){
                                detour_P = player;
                                obj_detour = 1;
                                detour = (gk.x() * a > ball.x() * a ? 1 * a : -1 * a);
                                state = ST_Detour;
                                return;
                            }
                        }
                    }
                }
                if(ball.x() * a > gk.x() * a){
                    obj_detour = 0;
                    state = ST_Detour;
                    detour = (gk.x() * a > ball.x() * a ? 1 * a : -1 * a);
                    return;
                }else Predictor(getPlayer(), wp).run(a, def_line.x(), 0.);
            }else Predictor(getPlayer(), wp).run(a, def_line.x(), 0.);

        break;
        }

        // Se algum obstáculo for encontra, desvia do mesmo antes de alguma ação
        case ST_Detour:{
            if((obj_detour ? Dribbler(getPlayer(), wp).run(detour, detour_P->getPosition(), radius) : Dribbler(getPlayer(), wp).run(detour, wp->ballPosition(), radius, -detour*radius*0.6)))
                state = ST_Search;
        break;
        }
    }


}
