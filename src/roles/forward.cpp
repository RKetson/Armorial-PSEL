#include "forward.h"
#include <QDebug>
// a = 1   ->  Jogando do lado direito
// a = -1  ->  Jogando do lado esquerdo

void Forward::run(int8_t a)
{
    typedef enum{
        ST_Search = 0, ST_Detour
    } States;

    static States state = ST_Search;

    WorldMap* wp = getWorldMap();
    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();
    QVector2D def_line = QVector2D(1.5 * radius, 0.);
    QVector2D fw = getPlayer()->getPosition();

    static Player* detour_P;
    static bool obj_detour;

    static int8_t detour;

    switch (state) {

        // Verifica se existe algum obstáculo e seleciona o behavior de acordo com sua posição
        case ST_Search:{
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
                            state = ST_Detour;
                            return;
                        }
                    }
                }
            }
            if(ball.x() * a > fw.x() * a){
                obj_detour = 0;
                state = ST_Detour;
                detour = (fw.x() * a > ball.x() * a ? 1 * a : -1 * a);
                return;
            }else if(ball.x() * a > def_line.x() * a)
                Predictor(getPlayer(), wp).run(a, def_line.x(), 0.);
            else Chaser(getPlayer(), wp).run(a);

        break;
        }

        // Se algum obstáculo for encontra, desvia do mesmo antes de alguma ação
        case ST_Detour:{
            if((obj_detour ? Dribbler(getPlayer(), wp).run(detour, detour_P->getPosition(), radius) : Dribbler(getPlayer(), wp).run(detour, wp->ballPosition(), radius * 1.3, -detour*radius*0.6)))
                state = ST_Search;
        break;
        }
    }

}
