#include "server/rocket_launcher.h"


RocketLauncher::RocketLauncher() : bullets_per_spray(5), fire_rate(1), precision(1),
                                    object_type("Rocket") {
}

RocketLauncher::~RocketLauncher()
{
}
