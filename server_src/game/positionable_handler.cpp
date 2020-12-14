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

Positionable PositionableHandler::createBlockingItem(std::string id) {
  if (id == "stone_wall") return Wall(id, false);
  else if (id == "wood_wall")  return Wall(id, false);
  else if (id == "blue_wall")  return Wall(id, false);
  else if (id == "rock_wall")  return Wall(id, false);
  else if (id == "barrel")  return Barrel();
  else { return Table(); }
}

Positionable PositionableHandler::createItem(std::string id) {
  if (id == "food") return Food();
  else if (id == "medkit") return MediKit();
  else if (id == "bullets") return Bullets(id);
  else if (id == "machine_gun") return MachineGun();
  else if (id == "chain_gun") return ChainGun();
  else if (id == "rpg_gun") return RocketLauncher();
  else if (id == "cross") return Cross();
  else if (id == "goblet") return Goblet();
  else if (id == "chest") return Chest();
  else if (id == "crown") return Crown();
  else { return Key(); }
}

