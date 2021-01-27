#ifndef TP_WOLFENSTEIN_COORDINATE_H
#define TP_WOLFENSTEIN_COORDINATE_H

#include <iostream>

class Coordinate {
public:
    int x;
    int y;
    Coordinate(int _x, int _y) : x(_x), y(_y) {}
    bool operator==(const Coordinate& p) const { return x == p.x && y == p.y; }
    bool operator<(const Coordinate& coord) const {
        if (x < coord.x) return true;
        if (x > coord.x) return false;
        if (y < coord.y) return true;
        if (y > coord.y) return false;
        return false;
    }
    bool operator!=(const Coordinate& c) const {
        return x != c.x || y != c.y;
    }
    Coordinate() {}
    ~Coordinate() {}
    void show() {
        std::cout << "Coord: (" << x << ", " << y << ")\n";
    }
    bool isValid() const {
        return x != -1 && y != -1;
    }
    int distanceTo(Coordinate other) {
        return (x - other.x) + (y - other.y);
    }

};


#endif //TP_WOLFENSTEIN_COORDINATE_H
