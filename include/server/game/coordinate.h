#ifndef TP_WOLFENSTEIN_COORDINATE_H
#define TP_WOLFENSTEIN_COORDINATE_H

#include <iostream>

class Coordinate {
public:
    int x;
    int y;

    Coordinate(int _x, int _y);
    Coordinate();
    ~Coordinate();

    bool operator<(const Coordinate& coord) const;

    bool operator!=(const Coordinate& c) const;

    void show() const;

    bool isValid() const;

    int distanceTo(const Coordinate& other) const;

    bool operator==(const Coordinate& p) const;

    struct HashFunction {
        size_t operator()(const Coordinate& c) const {
            size_t res = 1009;
            res = res * 9176 + std::hash<int>()(c.x);
            res = res * 9176 + std::hash<int>()(c.y);
            return res;
        }
    };
};

// https://stackoverflow.com/questions/1646807/quick-and-simple-hash-code-combinations/34006336#34006336

#endif //TP_WOLFENSTEIN_COORDINATE_H
