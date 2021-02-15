#include "server/events/hit_handler.h"
#include "server/game/gun_hotkeys.h"

HitHandler::HitHandler() {}

void HitHandler::processHit(Hit &hit_event, std::vector<Change> &changes, int players_alive) {
    // Obtengo vector de (enemy_id, daño hecho) //
    std::vector<std::pair<int, int>> dmg_done = hit_event.getEnemyDmgDone(players_alive);
    if (hit_event.getPlayerId() != -1) {
        changes.emplace_back(CHANGE_AMMO, hit_event.getPlayerId(),
                             -hit_event.getBulletsShot(), INVALID, true);
    }
    if (hit_event.usedAllAmmo() && hit_event.getPlayerId() != -1) {
        changes.emplace_back(CHANGE_WEAPON, hit_event.getPlayerId(),
                                 KNIFE, INVALID, true);
    }
    for (auto& hit : dmg_done) {
        changes.emplace_back(CHANGE_HP, hit.first,
                                 -hit.second, INVALID, true);
    }
    // Respawn: (id del player que muere, si respawnea o no) //
    for (auto& respawn : hit_event.getPlayerRespawns()) {
        if (respawn.second) {
            changes.emplace_back(RESPAWN_PLAYER, respawn.first, INVALID, INVALID, true);
            changes.emplace_back(CHANGE_WEAPON, respawn.first, PISTOL, INVALID, true);
        }
        else changes.emplace_back(KILL_PLAYER, respawn.first, INVALID, INVALID, true);
    }
    // Drop: Objeto con (tipo, id del item, pos, id del drop) //
    for (auto& drop : hit_event.getDrops()) {
        switch (drop.drop_id) {
            case (GUN_DROP): {
                if (drop.type == "machine_gun") {
                    changes.emplace_back(ADD_MACHINE_GUN_AT, drop.id, drop.pos.x, drop.pos.y, true);
                } else if (drop.type == "chain_gun") {
                    changes.emplace_back(ADD_CHAIN_GUN_AT, drop.id, drop.pos.x, drop.pos.y, true);
                } else if (drop.type == "rpg_gun") {
                    changes.emplace_back(ADD_RPG_GUN_AT, drop.id, drop.pos.x, drop.pos.y, true);
                } else {
                    break;
                }
                break;
            }
            case (KEY_DROP): {
                changes.emplace_back(ADD_KEY_AT, drop.id, drop.pos.x, drop.pos.y, true);
                break;
            }
            case (BULLETS_DROP): {
                changes.emplace_back(ADD_BULLETS_AT, drop.id, drop.pos.x, drop.pos.y, true);
                break;
            }
            default: {
                break;
            }
        }
    }
}

HitHandler::~HitHandler() {}
