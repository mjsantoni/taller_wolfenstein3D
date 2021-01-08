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

Positionable PositionableHandler::createBlockingItem(std::string type) {
  if (type == "stone_wall") return Wall(type, false);
  else if (type == "wood_wall")  return Wall(type, false);
  else if (type == "blue_wall")  return Wall(type, false);
  else if (type == "rock_wall")  return Wall(type, false);
  else if (type == "barrel")  return Barrel();
  else { return Table(); }
}

Positionable PositionableHandler::createItem(std::string type) {
  if (type == "food") return HPItem(type, "id", 10);
  else if (type == "medkit") return HPItem(type, "id", 20);
  else if (type == "bullets") return Bullets("id", 5);
  else if (type == "machine_gun") return Gun(type, "id", 5, 0.3, 0.6);
  else if (type == "chain_gun") return Gun(type, "id", 1, 0.1, 0.8);
  else if (type == "rpg_gun") return Gun(type, "id", 5, 1, 1);
  else if (type == "cross") return Treasure(type, "id", 10);
  else if (type == "goblet") return Treasure(type, "id", 50);
  else if (type == "chest") return Treasure(type, "id", 100);
  else if (type == "crown") return Treasure(type, "id", 200);
  else { return Key(); }
}

