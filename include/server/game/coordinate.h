#ifndef TP_WOLFENSTEIN_COORDINATE_H
#define TP_WOLFENSTEIN_COORDINATE_H

#include <iostream>

class Coordinate {
public:
    int x;
    int y;
    Coordinate(int _x, int _y) : x(_x), y(_y) {}

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
    int distanceTo(const Coordinate& other) {
        return (x - other.x) + (y - other.y);
    }

    bool operator==(const Coordinate& p) const { return x == p.x && y == p.y; }

    struct HashFunction{
        size_t operator()(const Coordinate& c) const {
            //Funcion1, anda mejor
            size_t res = 1009;
            res = res * 9176 + std::hash<int>()(c.x);
            res = res * 9176 + std::hash<int>()(c.y);

            //funcion2, anda bien tambien
            //int res = (c.x + c.y) * (c.x + c.y + 1) / 2 + c.y;
            return res;
        }
    };

};


#endif //TP_WOLFENSTEIN_COORDINATE_H
