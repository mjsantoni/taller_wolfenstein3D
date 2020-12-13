#ifndef TP_WOLFENSTEIN_COLISSION_HANDLER_H
#define TP_WOLFENSTEIN_COLISSION_HANDLER_H

#include "server/map.h"

class ColissionHandler {
private:
    Map& map;
    int move_size = 10;
    int safe_distance = 10;
public:
    ColissionHandler(Map& _map);
    std::pair<int, int> moveToPosition(std::pair<int,int> actual_pos, double angle);
    bool isValid(std::pair<int,int> new_position);

    Positionable getCloseItems(std::pair<int, int> old_pos, std::pair<int, int> new_pos);

    std::vector<std::pair<int, int>> walkedPositions(std::pair<int, int> old_pos,
                                                     std::pair<int, int> new_pos);
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