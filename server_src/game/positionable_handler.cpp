#include "server/game/positionable_handler.h"

#include <string>

#include "server/entities/barrel.h"
#include "server/entities/bullets.h"
#include "server/entities/key.h"
#include "server/entities/table.h"
#include "server/entities/wall.h"
#include "server/entities/treasure.h"
#include "server/entities/gun.h"
#include "server/entities/hp_item.h"
#include "server/entities/door.h"

PositionableHandler::PositionableHandler(std::string _config_path) :
                                           cp(_config_path) {}

Positionable PositionableHandler::createBlockingItem(std::string type, int id) {
  if (type == "stone_wall") return Wall(type, id, false);
  else if (type == "wood_wall")  return Wall(type, id, false);
  else if (type == "blue_wall")  return Wall(type, id, false);
  else if (type == "rock_wall")  return Wall(type, id, false);
  else if (type == "locked_door") return Door(type, id, true);
  else if (type == "unlocked_door") return Door(type, id, false);
  else if (type == "barrel")  return Barrel(id);
  else { return Table(id); }
}

Positionable PositionableHandler::createItem(std::string type, int id) {
  if (type == "food") return HPItem(type, id, cp.getSpecificCategory("hp_item", type));
  else if (type == "medkit") return HPItem(type, id, cp.getSpecificCategory("hp_item", type));
  else if (type == "bullets") return Bullets(id, cp.getBullets());
  else if (type == "machine_gun") return Gun(type, id, cp.getSpecificGun(type)[0], cp.getSpecificGun(type)[1],
                                             cp.getSpecificGun(type)[2], cp.getSpecificGun(type)[3]);
  else if (type == "chain_gun") return Gun(type, id, cp.getSpecificGun(type)[0], cp.getSpecificGun(type)[1],
                                           cp.getSpecificGun(type)[2], cp.getSpecificGun(type)[3]);
  else if (type == "rpg_gun") return Gun(type, id, cp.getSpecificGun(type)[0], cp.getSpecificGun(type)[1],
                                         cp.getSpecificGun(type)[2], cp.getSpecificGun(type)[3]);
  else if (type == "cross") return Treasure(type, id, cp.getSpecificCategory("treasure", type));
  else if (type == "goblet") return Treasure(type, id, cp.getSpecificCategory("treasure", type));
  else if (type == "chest") return Treasure(type, id, cp.getSpecificCategory("treasure", type));
  else if (type == "crown") return Treasure(type, id, cp.getSpecificCategory("treasure", type));
  else { return Key(id); }
}

