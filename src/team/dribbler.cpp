#include "dribbler.h"

void Dribbler::run(uint8_t a)
{
    typedef enum{
        ST_Search = 0, ST_Ajust, ST_Rotate, ST_Shoot
    } States;

    static States state = ST_Search;

    WorldMap* wp = getWorldMap();
    Player* dribbler = getPlayer();
}
