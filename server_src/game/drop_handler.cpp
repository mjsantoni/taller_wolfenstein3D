#include "server/game/drop_handler.h"
#include "server/entities/bullets.h"

DropHandler::DropHandler(std::string config_path) : configParser(config_path) {}

DropHandler::~DropHandler() {}

void DropHandler::processDrops(const std::pair<std::pair<std::string, int>, int>& drops,
                               Map &map, const Coordinate& pos) {
    if (drops.second != -1) {
        map.putPositionableAtExact(Key(drops.second),
                                   Coordinate(pos.x, pos.y + 2));
    }
    if (drops.first.first != "pistol") {
        std::vector<double> gun_stats = configParser.getSpecificGun(drops.first.first);
        Gun gun(drops.first.first, drops.first.second,
                gun_stats[0], gun_stats[1], gun_stats[2], gun_stats[3]);
        map.putPositionableAtExact(gun, Coordinate(pos.x, pos.y - 2));
    }
    map.putPositionableAtExact(Bullets(map.getGlobalID(), configParser.getBullets() * 2),
                               Coordinate(pos.x + 2, pos.y));
    map.addGlobalID();
}

