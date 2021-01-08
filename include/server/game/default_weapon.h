#ifndef TP_WOLFENSTEIN_DEFAULT_WEAPON_H
#define TP_WOLFENSTEIN_DEFAULT_WEAPON_H
#include <string>

class DefaultWeapon {
protected:
    std::string type;
    int damage;
    int bullets_per_spray;
    double fire_rate;
    double precision;
public:
    DefaultWeapon(int _bullets_per_spray, double _fire_rate,
        double _precision, std::string _type);
    std::string getType();

    ~DefaultWeapon();
};



#endif //TP_WOLFENSTEIN_DEFAULT_WEAPON_H
