#include "common/hit_handler.h"
#include "server/game/gun_hotkeys.h"

HitHandler::HitHandler() {}

void HitHandler::processHit(Hit& hit_event, std::vector<Change>& changes) {
    std::vector<std::pair<int, int>> dmg_done = hit_event.getEnemyDmgDone(2); // maxplayers viene por parametro
    changes.push_back(Change(CHANGE_AMMO, hit_event.getPlayerId(),
                             -hit_event.getBulletsShot(), -1, false));
    if (hit_event.usedAllAmmo()) {
        changes.push_back(Change(CHANGE_WEAPON, hit_event.getPlayerId(),
                                 KNIFE, -1, false));
    }
    for (auto& hit : dmg_done) {
        changes.push_back(Change(CHANGE_HP, hit.first,
                                 -hit.second, -1, false));
    }
    for (auto& respawn : hit_event.getPlayerRespawns()) {
        if (respawn.second) changes.push_back(Change(RESPAWN_PLAYER, respawn.first, -1, -1, true));
        else changes.push_back(Change(KILL_PLAYER, respawn.first, -1, -1, true));
    }
    for (auto& drop : hit_event.getDrops()) {
        switch (drop.drop_id) {
            case (GUN): {
                changes.push_back(Change(ADD_GUN_AT, drop.id, drop.pos.x, drop.pos.y, true));
                break;
            }
            case (KEY): {
                changes.push_back(Change(ADD_KEY_AT, drop.id, drop.pos.x, drop.pos.y, true));
                break;
            }
            case (BULLETS): {
                changes.push_back(Change(ADD_BULLETS_AT, drop.id, drop.pos.x, drop.pos.y, true));
                break;
            }
            default: {
                break;
            }
        }
    }
}

HitHandler::~HitHandler() {}

