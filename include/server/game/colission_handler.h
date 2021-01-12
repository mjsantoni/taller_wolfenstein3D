#ifndef TP_WOLFENSTEIN_COLISSION_HANDLER_H
#define TP_WOLFENSTEIN_COLISSION_HANDLER_H

#include "map.h"
#include "coordinate.h"

class ColissionHandler {
private:
    Map& map;
    int move_size = 10;
    int safe_distance = 10;
public:
    explicit ColissionHandler(Map &_map);
    Coordinate moveToPosition(Coordinate actual_pos, double angle);
    //bool isValid(Coordinate new_position);

    Positionable getCloseItems(Coordinate old_pos,
                               Coordinate new_pos,
                               Coordinate& pos_positionable);
};


#endif //TP_WOLFENSTEIN_COLISSION_HANDLER_H

/*
if (bloqueante) {
    break
} else {
    Positionable item;
    pos = hay algo aca(item) //iterar alrededor
    if (item != null)
        player.pickup(item)
        map.erasePositionableAt(pos)

    continue
}

std::position de par hay algo aca(&item):
    for en todas direcciones de 5 pos aprox
        colision no bloqueante? pongo ese algo y la pos
    pongo null




una vez q tengo la pos, vuelvo buscando por la diagonal si me encontre con algo
funcion: buscaritems

if Yn - Yv == 0 -> itera todas tus xi
if Xn - Xv == 0 -> itera todas tu yi
sino hace la pendiente normal

 */