#include "server/default_weapon.h"


DefaultWeapon::DefaultWeapon(int _bullets_per_spray, double _fire_rate,
                             double _precision, std::string _type) :
                             bullets_per_spray(_bullets_per_spray),
                             fire_rate(_fire_rate), precision(_precision),
                             type(_type) {

}

DefaultWeapon::~DefaultWeapon() {

}