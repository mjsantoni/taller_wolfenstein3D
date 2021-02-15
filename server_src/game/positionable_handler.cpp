#include "server/game/positionable_handler.h"

#include <string>
#include "server/entities/barrel.h"
#include "server/entities/table.h"
#include "server/entities/wall.h"
#include "server/entities/door.h"

PositionableHandler::PositionableHandler(const std::string& _config_path) :
                                           cp(_config_path) {}

Positionable PositionableHandler::createBlockingItem(const std::string& type, int id) {
  if (type == "stone_wall") return Wall(type, id, false);
  else if (type == "wood_wall")  return Wall(type, id, false);
  else if (type == "blue_wall")  return Wall(type, id, false);
  else if (type == "rock_wall")  return Wall(type, id, false);
  else if (type == "locked_door") return Door(type, id, true);
  else if (type == "unlocked_door") return Door(type, id, false);
  else if (type == "barrel")  return Barrel(id);
  else { return Table(id); }
}

Positionable PositionableHandler::createItem(const std::string& type, int id) {
  if (type == "food" || type == "medkit" || type == "blood_puddle")
      return Positionable("hp_item", type, id, false);
  else if (type == "bullets")
      return Positionable("bullets", type, id, false);
  else if (type == "machine_gun" || type == "chain_gun" || type == "rpg_gun")
      return Positionable("gun", type, id, false);
  else if (type == "cross" || type == "goblet" || type == "chest" || type == "crown")
      return Positionable("treasure", type, id, false);
  else if (type == "water_puddle")
      return Positionable("water_puddle", "water_puddle", id, false);
  else
      return Positionable("key", "key", id, false);
}

