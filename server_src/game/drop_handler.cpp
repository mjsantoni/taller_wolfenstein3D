#include "server/game/drop_handler.h"
#include "server/entities/bullets.h"
#include <iostream>

DropHandler::DropHandler(std::string config_path, Map &_map) :
                            configParser(config_path),
                            map(_map) {}

DropHandler::~DropHandler() {}

void DropHandler::processDrops(const std::vector<Drop> &drops) {
    for (auto& drop : drops) {
        switch (drop.drop_id) {
            case (GUN): {
                std::vector<double> gun_stats = configParser.getSpecificGun(drop.type);
                Gun gun(drop.type, drop.id, gun_stats[0], gun_stats[1], gun_stats[2], gun_stats[3]);
                map.putPositionableAt(gun, drop.pos);
                break;
            }
            case (KEY): {
                map.putPositionableAt(Key(drop.id), drop.pos);
                break;
            }
            case (BULLETS): {
                map.putPositionableAt(Bullets(drop.id,
                                              configParser.getSpecificCategory("bullets", "dropped_bullets"),
                                              "dropped_bullets"),
                                               drop.pos);
                break;
            }
            default: {
                break;
            }

        }
    }
}

