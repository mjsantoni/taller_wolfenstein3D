#include "server/events/bots_manager.h"
#include <iostream>
#include "routes_server.h"

BotsManager::BotsManager(SharedQueue<Event>& sq) : sharedQueue(sq) {}

void BotsManager::addBot(Player& player, double angle_turn) {
  std::cout << "[Bots Manager] Creating bot.\n";
  LuaBot* bot = new LuaBot(BOT_SCRIPT_PATH, player, cv, sharedQueue);
  bot->setGridSize(64); // map.getGridSize()
  bot->setAngleTurn(angle_turn);
  bot->start();
  bots.push_back(bot);
}

void BotsManager::sendMapToBot(LuaBot* bot, Map& map, std::vector<Player>& players) {
  for (auto& item : map.getBoard()) {
    Coordinate coord = item.first;
    Positionable& positionable = item.second;
    if (positionable.getCategory() == "wall" ||
        positionable.getCategory() == "door" ||
        positionable.getCategory() == "misc") {
      bot->addBlocking(coord, positionable.getType());
    } else {
      bot->addPositionable(coord, positionable.getType());
    }
  }
  for (auto& player : players) {
    if (player.getID() == bot->getId()) continue;
    else if (!player.hasLives()) continue;
    else bot->addPlayer(map.getPlayerPosition(player.getID()), player.getID());
  }
}

void BotsManager::releaseBots(Map& map, std::vector<Player>& players) {
  if (!probability(0.04)) return;
  for (auto& bot : bots) {
    bot->updatePosition(map.getPlayerPosition(bot->getId()));
    bot->setGunRange(players[bot->getId()].getGun().getRange());
    bot->cleanMap();
    bot->sendLives(players[bot->getId()].getLives());
    usleep(300000);
    sendMapToBot(bot, map, players);
  }
  cv.notify_all();
}

void BotsManager::destroyBots() {
  std::cout << "[Bots Manager] Destroying bots.\n";
  for (auto& bot : bots) {
    bot->stop();
  }
  cv.notify_all();
  for (auto& bot : bots) {
    bot->join();
    delete bot;
  }
}

BotsManager::~BotsManager() {}
