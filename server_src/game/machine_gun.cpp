#include "server/machine_gun.h"

MachineGun::MachineGun() : bullets_per_spray(1), fire_rate(0.1), precision(0.8),
                            object_type("MachineGun") {
}

MachineGun::~MachineGun() {
}