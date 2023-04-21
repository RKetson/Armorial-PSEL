#include "forward.h"
// a = 1   ->  Jogando do lado direito
// a = -1  ->  Jogando do lado esquerdo
void Forward::run(int8_t a)
{
    WorldMap* wp = getWorldMap();
    QVector2D def_line = zero;
    QVector2D ball = wp->ballPosition();
    float radius = wp->centerRadius();
}
