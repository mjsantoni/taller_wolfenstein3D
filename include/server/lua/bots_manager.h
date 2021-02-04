#ifndef TP_WOLFENSTEIN_BOTS_MANAGER_H
#define TP_WOLFENSTEIN_BOTS_MANAGER_H

#include "server/game/coordinate.h"
#include "server/game/positionable.h"
#include "server/lua/lua_bot.h"
#include "server/game/map.h"
#include "server/game/player.h"
#include <mutex>
#include <vector>
#include <iostream>

class BotsManager {
private:
    std::vector<LuaBot*> bots;
    std::condition_variable cv;

public:
    BotsManager() {}

    void addBot(Player& player) {
        LuaBot* bot = new LuaBot("../server_src/lua/bot.lua", player, cv);
        bot->setGridSize(64); // map.getGridSize()
        bot->setAngleTurn(M_PI / 8);
        bot->start();
        bots.push_back(bot);
    }
    void sendMapToBot(LuaBot* bot, Map& map, std::vector<Player>& players) {
        for (auto& item : map.getBoard()) {
            Coordinate coord = item.first;
            Positionable& positionable = item.second;
            if (positionable.getCategory() == "wall" ||
                positionable.getCategory() == "door" ||
                positionable.getCategory() == "barrel" ||
                positionable.getCategory() == "table") {
                bot->addBlocking(coord, positionable.getType());
            } else {
                bot->addPositionable(coord, positionable.getType());
            }
        }
        for (auto& player : players) {
            if (player.getID() == bot->getId()) continue;
            bot->addPlayer(map.getPlayerPosition(player.getID()), player.getID());
        }
        bot->printMap();

    }

    void releaseBots(Map& map, std::vector<Player>& players) {
        for (auto& bot : bots) {
            bot->cleanMap();
            sendMapToBot(bot, map, players);
            bot->updatePosition(map.getPlayerPosition(bot->getId()));
        }
        cv.notify_all();
    }

    void destroyBots() {
        std::cout << "DESTRUCTOR DE GAME -> MATA BOTS\n";
        for (auto& bot : bots) {
            bot->stop();
        }
        cv.notify_all();
        for (auto& bot : bots) {
            bot->join();
            delete bot;
        }
    }

};

#endif //TP_WOLFENSTEIN_BOTS_MANAGER_H
