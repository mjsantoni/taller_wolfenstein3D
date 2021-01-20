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
    Coordinate moveToPosition(const Coordinate& actual_pos, double angle);

    std::vector<std::pair<Coordinate, Positionable>>
        getCloseItems(const Coordinate& old_pos, const Coordinate& new_pos);

    Coordinate getCloseBlocking(Coordinate pos, double angle, std::string category);
};

#endif //TP_WOLFENSTEIN_COLISSION_HANDLER_H
