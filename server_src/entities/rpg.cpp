#include "server/entities/rpg.h"

RPG::RPG(int _current_position, std::vector<Coordinate> _path, int _player_id, int _rpg_id) :
        current_position(_current_position),
        path(std::move(_path)),
        player_id(_player_id),
        current_coord(path[current_position]),
        rpg_id(_rpg_id) {}

int RPG::getCurrentPosition() const { return current_position; }

std::vector<Coordinate>& RPG::getPath() { return path; }

int RPG::getPlayerId() const { return player_id; }

void RPG::setCurrentPosition(int new_pos) { current_position = new_pos; }

void RPG::setCurrentCoordinate(const Coordinate& coordinate) { current_coord = coordinate; }

const Coordinate& RPG::getCurrentCoord() const { return current_coord; }

int RPG::getRpgId() const { return rpg_id; }

bool RPG::exploded() const { return rpg_exploded; }

void RPG::explode() { rpg_exploded = true; }
