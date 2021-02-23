#include "server/events/event_processor.h"
#include "server/events/hit_handler.h"

EventProcessor::EventProcessor(Game& _game, const std::string& config_path) :
    game(_game), configParser(config_path) {}

std::vector<Change> EventProcessor::process(Event& event) {
  int id = event.event_id;
  int player_id = event.player_id;
  int value = event.value;
  std::vector<Change> changes;

  if (!game.isPlayerAlive(player_id)) { return changes; }
  switch (id) {
    case (CONNECT_PLAYER): {
      changes.emplace_back(TOTAL_PLAYERS_CONNECTED, game.getPlayersAlive(), INVALID, INVALID, true);
      break;
    }
    case (MOVE_PLAYER): {
      movePlayer(player_id, value, changes);
      break;
    }
    case (SHOOT): {
      std::pair<Hit, std::vector<Change>> hit_event = game.shoot(player_id);
      for (auto& change : hit_event.second) changes.push_back(change);

      HitHandler hit_handler;
      hit_handler.processHit(hit_event.first, changes, game.getPlayersAlive());
      break;
    }
    case (OPEN_DOOR): {
      std::pair<bool, int> opened_door = game.openDoor(player_id);
      bool use_key = opened_door.first;
      int door_id = opened_door.second;

      if (door_id == -1) break;

      changes.emplace_back(REMOVE_POSITIONABLE, door_id, player_id, INVALID, true);
      if (use_key)
        changes.emplace_back(CHANGE_KEY, player_id, -1, INVALID, false);
      break;
    }
    case (PUSH_WALL): {
      int pushed_wall_id = game.pushWall(player_id);
      if (pushed_wall_id == -1) break;
      changes.emplace_back(REMOVE_POSITIONABLE, pushed_wall_id, player_id, INVALID, true);
      break;
    }
    case (TURN_CAMERA): {
      game.rotate(player_id, value);
      break;
    }
    case (CHANGE_GUN): {
      int new_hotkey = game.changeGun(player_id, value); // value == hotkey
      changes.emplace_back(CHANGE_WEAPON, player_id, new_hotkey, INVALID, true);
      break;
    }
    case (PLAYER_READY): {
      game.playerIsReady(event.getPlayerID());
    }
    default: {
      break;
    }
  }
  return changes;
}

void EventProcessor::movePlayer(int player_id, int value, std::vector<Change>& changes) {
  bool has_ammo;
  std::pair<Coordinate,
            std::vector<Positionable>> move_changes = game.movePlayer(player_id, value, has_ammo);
  changes.emplace_back(MOVE_PLAYER, player_id,
                       move_changes.first.x, move_changes.first.y, true);
  for (auto& item : move_changes.second) {
    changes.emplace_back(REMOVE_POSITIONABLE, item.getId(), player_id, INVALID, true);

    if (item.getCategory() == "treasure") {
      changes.emplace_back(CHANGE_POINTS, player_id,
                           configParser.getSpecificCategory(item.getCategory(), item.getType()),
                           INVALID, false);
    } else if (item.getCategory() == "hp_item") {
      changes.emplace_back(CHANGE_HP, player_id,
                           configParser.getSpecificCategory(item.getCategory(), item.getType()),
                           INVALID, false);
    } else if (item.getCategory() == "bullets") {
      changes.emplace_back(CHANGE_AMMO, player_id,
                           configParser.getSpecificCategory(item.getCategory(), item.getType()),
                           INVALID, false);
      if (!has_ammo) {
        int gun_id = game.getPlayerGun(player_id);
        changes.emplace_back(CHANGE_WEAPON, player_id, gun_id, INVALID, true);
      }
    } else if (item.getCategory() == "key") {
      changes.emplace_back(CHANGE_KEY, player_id, 1, INVALID, false);
    }
  }
}
