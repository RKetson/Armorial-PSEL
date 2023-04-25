#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include "src/entities/player/player.h"
#include "src/entities/worldmap/worldmap.h"
#include <optional>

class Behavior
{
public:

    typedef enum{
        STD_Search = 0, STD_Detour
    } States_Dribbler;

    typedef enum{
        STC_Ajust = 0, STC_Rotate, STC_Goal, STC_Back
    } States_Chaser;

    typedef enum{
        STP_Search = 0, STP_Ajust, STP_Rotate, STP_Shoot
    } States_Predictor;

    typedef struct States
    {
        States_Dribbler ST_D = STD_Search;
        States_Chaser ST_C = STC_Ajust;
        States_Predictor ST_P = STP_Search;
    } States;

    Behavior(Player* player, WorldMap* wp);

    void run();
    WorldMap* getWorldMap();
    Player* getPlayer();

    QVector2D zero = QVector2D(0, 0);

protected:
    friend class Roles;
    void go(Player* player, QVector2D targetPosition);
    void rotate(Player* player, QVector2D targetPosition);
    void rotate(Player* player, float orientation);

private:
    Player* _player;
    WorldMap* _wp;
};

#endif // BEHAVIOR_H
