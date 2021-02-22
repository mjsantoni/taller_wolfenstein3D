#include "common/coordinate.h"

Coordinate::Coordinate(int _x, int _y) : x(_x), y(_y) {}

Coordinate::Coordinate() {}

Coordinate::~Coordinate() {}

bool Coordinate::operator<(const Coordinate& coord) const {
  if (x < coord.x) return true;
  if (x > coord.x) return false;
  if (y < coord.y) return true;
  if (y > coord.y) return false;
  return false;
}

bool Coordinate::operator!=(const Coordinate& c) const {
  return x != c.x || y != c.y;
}

void Coordinate::show() const {
  std::cout << "Coord: (" << x << ", " << y << ")\n";
}

bool Coordinate::isValid() const { return x != -1 && y != -1; }

int Coordinate::distanceTo(const Coordinate& other) const {
  return std::abs((x - other.x)) + std::abs((y - other.y));
}

bool Coordinate::operator==(const Coordinate& p) const { return x == p.x && y == p.y; }
