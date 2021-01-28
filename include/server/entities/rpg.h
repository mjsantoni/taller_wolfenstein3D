#ifndef TP_WOLFENSTEIN_RPG_H
#define TP_WOLFENSTEIN_RPG_H


class RPG {
private:
    int current_position;
    std::vector<Coordinate> path;
    int player_id;
    Coordinate current_coord;
    int rpg_id;
    bool rpg_exploded = false;

public:
    RPG(int _current_position, std::vector<Coordinate> _path, int _player_id, int _rpg_id) :
        current_position(_current_position),
        path(std::move(_path)),
        player_id(_player_id),
        current_coord(path[current_position]),
        rpg_id(_rpg_id) {}

    int getCurrentPosition() const {
        return current_position;
    }

    std::vector<Coordinate> &getPath() {
        return path;
    }
    int getPlayerId() const {
        return player_id;
    }

    void setCurrentPosition(int new_pos) {
        current_position = new_pos;
    }

    void setCurrentCoordinate(Coordinate coordinate) {
        current_coord = coordinate;
    }

    const Coordinate& getCurrentCoord() const {
        return current_coord;
    }
    int getRpgId() const {
        return rpg_id;
    }

    bool exploded() const {
        return rpg_exploded;
    }
    void explode() {
        rpg_exploded = true;
    }
};


#endif //TP_WOLFENSTEIN_RPG_H
