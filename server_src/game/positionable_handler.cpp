#include "server/positionable_handler.h"

#include <string>

#include "server/barrel.h"
#include "server/bullets.h"
#include "server/chain_gun.h"
#include "server/chest.h"
#include "server/cross.h"
#include "server/crown.h"
#include "server/food.h"
#include "server/goblet.h"
#include "server/key.h"
#include "server/machine_gun.h"
#include "server/medikit.h"
#include "server/rocket_launcher.h"
#include "server/table.h"
#include "server/wall.h"

Positionable PositionableHandler::createBlockingItem(std::string type) {
  if (type == "stone_wall") return Wall(type, false);
  else if (type == "wood_wall")  return Wall(type, false);
  else if (type == "blue_wall")  return Wall(type, false);
  else if (type == "rock_wall")  return Wall(type, false);
  else if (type == "barrel")  return Barrel();
  else { return Table(); }
}

Positionable PositionableHandler::createItem(std::string type) {
  if (type == "food") return Food();
  else if (type == "medkit") return MediKit();
  else if (type == "bullets") return Bullets();
  else if (type == "machine_gun") return MachineGun();
  else if (type == "chain_gun") return ChainGun();
  else if (type == "rpg_gun") return RocketLauncher();
  else if (type == "cross") return Cross();
  else if (type == "goblet") return Goblet();
  else if (type == "chest") return Chest();
  else if (type == "crown") return Crown();
  else { return Key(); }
}

