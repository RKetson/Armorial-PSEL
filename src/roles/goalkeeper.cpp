#include "goalkeeper.h"
#include "src/behaviors/dribbler.h"
#include "src/behaviors/predictor.h"
#include <QDebug>

void Goalkeeper::setListPlayers(const QMap<bool, QList<Player*>>& Players){
    _players = Players;
}

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

    static Player* detour_P;
    static bool obj_detour;

    static int8_t detour;

    qDebug() << detour;

    switch (state) {
        case ST_Search:{

            if(ball.x() * a > def_line.x() * a){
                for(int i = 0; i <= 1; i++){
                    for(const auto& player : _players.value(i)){
                        if((player->isTeamBlue() != getPlayer()->isTeamBlue()) || (player->getPlayerId() != getPlayer()->getPlayerId())){
                            if((gk - player->getPosition()).distanceToPoint(zero) < wp->centerRadius()){
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
        case ST_Detour:{
            if((obj_detour ? Dribbler(getPlayer(), wp).run(detour, detour_P->getPosition()) : Dribbler(getPlayer(), wp).run(detour, wp->ballPosition())))
                state = ST_Search;
        break;
        }
    }


}
