#ifndef TP_WOLFENSTEIN_RPG_H
#define TP_WOLFENSTEIN_RPG_H

#include <vector>
#include "server/game/coordinate.h"

class RPG {
private:
    int current_position;
    std::vector<Coordinate> path;
    int player_id;
    Coordinate current_coord;
    int rpg_id;
    bool rpg_exploded = false;

public:
    RPG(int _current_position, std::vector<Coordinate> _path, int _player_id, int _rpg_id);

    int getCurrentPosition() const;

    std::vector<Coordinate>& getPath();

    int getPlayerId() const;

    void setCurrentPosition(int new_pos);

    void setCurrentCoordinate(Coordinate coordinate);

    const Coordinate& getCurrentCoord() const;

    int getRpgId() const;

    bool exploded() const;

    void explode();
};

#endif //TP_WOLFENSTEIN_RPG_H
