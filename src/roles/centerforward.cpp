#include "centerforward.h"
#include <QDebug>

void CenterForward::run(int8_t a, States* state){

    WorldMap* wp = getWorldMap();
    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();
    QVector2D def_line = QVector2D(1.5 * radius * (-a), 0.);
    QVector2D fw = getPlayer()->getPosition();

    static Player* detour_P;
    static bool obj_detour;

    static int8_t detour;

    //qDebug() << detour;

    switch (state->ST_D) {

    // Verifica se existe algum obstáculo e seleciona o behavior de acordo com sua posição
        case STD_Search:{
            for(int i = 0; i <= 1; i++){
                for(const auto& player : _players.value(i)){
                    if((player->isTeamBlue() != getPlayer()->isTeamBlue()) || (player->getPlayerId() != getPlayer()->getPlayerId())){
                        float ang_pp = Utils::getAngle(fw, player->getPosition());
                        float ang_pb = Utils::getAngle(fw, ball);
                        //qDebug() << player->isTeamBlue() << player->getPlayerId() << ang_pp << ang_pb;
                        if((fw - player->getPosition()).distanceToPoint(zero) < wp->centerRadius() && (ang_pp < ang_pb + M_PI / 4 && ang_pp > ang_pb - M_PI / 4)){
                            detour_P = player;
                            obj_detour = 1;
                            detour = (fw.x() * a > ball.x() * a ? 1 * a : -1 * a);
                            state->ST_D = STD_Detour;
                            return;
                        }
                    }
                }
            }
            if(ball.x() * a > fw.x() * a){
                obj_detour = 0;
                state->ST_D = STD_Detour;
                detour = (fw.x() * a > ball.x() * a ? 1 * a : -1 * a);
                return;
            }else if((ball.x() * a >= -(wp->maxX() - radius*1.5)) && (ball.x() * a <= zero.x())){
                Chaser(getPlayer(), wp).run(a, state);
                state->ST_P = STP_Search;
            }
            else{
                Predictor(getPlayer(), wp).run(a, def_line.x(), radius * 1.5, state);
                state->ST_C = STC_Ajust;
            }

        break;
        }

        // Se algum obstáculo for encontra, desvia do mesmo antes de alguma ação
        case STD_Detour:{
            if((obj_detour ? Dribbler(getPlayer(), wp).run(detour, detour_P->getPosition(), radius) : Dribbler(getPlayer(), wp).run(detour, wp->ballPosition(), radius, -detour*radius*0.6)))
                state->ST_D = STD_Search;
        break;
        }
    }

}
