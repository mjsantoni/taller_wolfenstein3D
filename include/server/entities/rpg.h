#ifndef TP_WOLFENSTEIN_RPG_H
#define TP_WOLFENSTEIN_RPG_H


class RPG {
private:
    int current_position;
    std::vector<Coordinate> path;
    int trail_left;
public:
    RPG(int _current_position, std::vector<Coordinate> _path, int _trail_left) :
        current_position(_current_position),
        path(std::move(_path)),
        trail_left(_trail_left) {}
};


#endif //TP_WOLFENSTEIN_RPG_H
