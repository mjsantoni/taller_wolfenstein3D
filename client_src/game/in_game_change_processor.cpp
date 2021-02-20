
#include "client/game/in_game_change_processor.h"

#define MAX_CHANGES 5
#define MAX_ITERATIONS 25
#define MAX_WEAPON_ANIMATION 3
#define ENEMY_DEATH_ANIMATION 1
#define ENEMY_ATTACKING_ANIMATION 1

/* Recibe lo necesario para poder aplicar los cambios sobre la vista.
 * Por ejemplo del lado del eventProcessor recibe el objeto Game y
 * el configHandler
 */
InGameChangeProcessor::InGameChangeProcessor(GameScreen& _screen,
                                         ClientMap& _map,
                                         ClientPlayer& _player,
                                         SharedQueue<Change>& _change_queue,
                                         AudioManager& _audio_manager,
                                         StatisticsManager& _statistics_manager,
                                         bool& _player_alive,
                                         bool& _game_running) :
                                 screen(_screen),
                                 map(_map),
                                 player(_player),
                                 change_queue(_change_queue),
                                 game_over(false),
                                 audio_manager(_audio_manager),
                                 statistics_manager(_statistics_manager),
                                 player_alive(_player_alive),
                                 game_running(_game_running) {
}

/* Ejecuta los cambios */
void InGameChangeProcessor::processInGameChange(Change &change) {
    if (change.isInvalid()) {
        skip_rendering = true;
        return;
    }
    int change_id = change.change_id;
    int id = change.id;
    int value1 = change.value1;
    int value2 = change.value2;

    if (!player_alive || game_over)
        processPostGameChanges(change);

    //std::cout<< "Se procesa el cambio " << change_id << " con id " << id << " y valores " << value1 << " y " << value2 << std::endl;
    // render ray_caster, render object_drawer, render ui_drawer
    switch (change_id) {
        case (REMOVE_POSITIONABLE): {
            return processObjectRemoval(id, value1);
        }
        case (MOVE_PLAYER): {
            if (player.getId() == id) {
                player.updatePosition(value1, value2);
            } else {
                map.moveEnemy(id, value1, value2);
            }
            break;
        }
        case (CHANGE_POINTS): {
            if (player.getId() != id)
                break;
            player.updateScore(value1);
            render_background_and_objects = false;
            // id: player_id - value1: points to add
            break;
        }
        case (CHANGE_HP): {
            if (player.getId() != id)
                return processEnemyHealthChange(id, value1);
            return processPlayerHealthChange(value1);
        }
        case (CHANGE_AMMO): {
            int ammo_delta = value1;
            if (player.getId() != id)
                return processEnemyAmmoChange(id, ammo_delta);
            return processPlayerAmmoChange(ammo_delta);
        }
        case (CHANGE_KEY): {
            if (player.getId() != id)
                break;
            player.updateKeys(value1);
            render_background_and_objects = false;
            break;
        }
        case (CHANGE_WEAPON): {
            if (player.getId() == id) {
                player.changeWeapon(value1);
                render_background_and_objects = false;
            }
            else {
                map.changeEnemyImage(id, value1);
            }
            break;
        }
        case (KILL_PLAYER): {
            if (player.getId() == id) {
                screen.displayDeadScreen();
                sleep(2);
                player_alive = false;
                //algo mas aca seguro
            } else {
                processEnemyDying(id);
            }
            break;
        }
        case (RESPAWN_PLAYER): {
            std::cout << "RESPAWNING\n";
            if (player.getId() == id) {
                player.respawn();
                screen.displayRespawningScreen();
                sleep(2);
            } else {
                return processEnemyRespawning(id);
            }
        }
        case (ADD_PLAYER): {
            player.setId(id);
            std::pair<int, int> player_pos = map.getSpawnPositionForPlayer(id);
            player.setMapPosition(player_pos);
            break;
        }
        case (ADD_BULLETS_AT): {
            map.putObjectAt(id, ITEM_BULLETS, value1, value2);
            // id: nuevo id_bullets - value1: new_x - value2: new_y
            break;
        }
        case (ADD_BLOOD_PUDDLE_AT): {
            map.putObjectAt(id, ITEM_BLOOD, value1, value2);
            // id: nuevo id_bullets - value1: new_x - value2: new_y
            break;
        }
        case (ADD_KEY_AT): {
            map.putObjectAt(id, ITEM_KEY, value1, value2);
            // id: nuevo id_key - value1: new_x - value2: new_y
            break;
        }
        case (ADD_MACHINE_GUN_AT): {
            map.putObjectAt(id, ITEM_MACHINE_GUN, value1, value2);
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_CHAIN_GUN_AT): {
            map.putObjectAt(id, ITEM_CHAIN_CANNON, value1, value2);
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_RPG_GUN_AT): {
            map.putObjectAt(id, ITEM_ROCKET_LAUNCHER, value1, value2);
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_UNLOCKED_DOOR): {
            map.updateUnlockedDoor(id, value1, value2);
            // id: new_item_id - value1: new_x - value2: new_y (viene de cerrar puerta)
            break;
        }
        case (RPG_MOVE_TO): {
            map.updateRPGMissile(id, value1, value2);
            // id: mismo rpg_id - value1: new_x - value2: new_y (utilizar los viejos x,y para hacer la animacion)
            break;
        }
        case (RPG_EXPLODE_AT): {
            double distance_ratio =
                    map.setRPGMissileExplosion(id, value1, value2);
            audio_manager.displayExplosionSound(distance_ratio);
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
        /*
        case (TOTAL_PLAYERS_CONNECTED): {
            map.addPlayers(id, player.getId());
            render_vector = std::vector<int>{0, 1, 0};
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
         */
        case (CL_UPDATE_DIRECTION): {
            player.updateDirection(value2);
            break;
        }
        default: {
            break;
        }
    }
    //std::cout << "pos del jugador: (" << player.getXPosition() << "," << player.getYPosition() << ")\n";
}

void InGameChangeProcessor::processInGameChanges() {
    Change change = change_queue.pop();
    processInGameChange(change);
    if (game_over) {
        return;
    }
    if (!skip_rendering || mandatory_rendering_turns != 0)
        screen.render(render_background_and_objects);
    if (counter % 10 == 0)
        map.updateEnemiesSprites();
    map.updateEvents();
    ++counter;
    render_background_and_objects = true;
    skip_rendering = false;
    if (mandatory_rendering_turns > 0)
        --mandatory_rendering_turns;
}
/*
void InGameChangeProcessor::processInGameChanges(std::vector<Change> changes) {
    for (auto& change : changes) {
        std::cout << "Se procesa un cambio " << change.getChangeID() << std::endl;
        processInGameChange(change);
    }
}
*/
void InGameChangeProcessor::stop() {
    game_over = false;
}

void InGameChangeProcessor::processPostGameChanges(Change change) {
    int change_id = change.getChangeID();
    if (change_id == GAME_OVER) {
        game_running = false;
        if (!player_alive) {
            audio_manager.playDefeatSong();
            screen.displayDefeatScreen();
        }
        return;
    }
    if (change_id < TOP_KILLER || change_id > TOP_SCORER)
        return;
    int player_id = change.getPlayerID();
    int value = change.getFirstValue();
    int position = change.getSecondValue();
    statistics_manager.addStatistic(change_id, player_id, value, position);
}

void InGameChangeProcessor::processEnemyAmmoChange(int enemy_id, int value) {
    if (value > 0) {
        render_background_and_objects = false;
        return;
    }
    int enemy_type = map.getEnemyTypeFromId(enemy_id);
    if (enemy_type != ENEMY_DOG && value == 0) {
        render_background_and_objects = false;
        return;
    }
    map.setEnemyAttacking(enemy_id);
    updateMandatoryRenderingTurns(ENEMY_ATTACKING_ANIMATION+1);
    double distance_ratio = map.getEnemyDistanceRatio(enemy_id);
    if (enemy_type == ENEMY_DOG)
        audio_manager.displayDogAttackingSound(distance_ratio);
    else
        audio_manager.displayEnemyShot(distance_ratio);
}

void InGameChangeProcessor::processPlayerAmmoChange(int delta) {
    if (delta < 0) {
        audio_manager.displayPlayerShootingSound();
        screen.setPlayerAttacking();
        mandatory_rendering_turns = MAX_WEAPON_ANIMATION+1;
        render_background_and_objects = false;
    }
    else if (delta == 0) {
        if (player.getEquippedWeapon() != 1) {
            audio_manager.displayEmptyGunSound();
            //skip_rendering = true;
        }
        else {
            audio_manager.displayKnifeStabbingSound();
            //screen.displayPlayerAttacking();
            screen.setPlayerAttacking();
            updateMandatoryRenderingTurns(MAX_WEAPON_ANIMATION+1);
        }
    }
    player.updateAmmo(delta);
}

void InGameChangeProcessor::processEnemyHealthChange(int enemy_id,
                                                     int delta) {

        if (delta < 0) {
            map.setBloodEffectForEnemy(enemy_id);
            int enemy_type = map.getEnemyTypeFromId(enemy_id);
            double distance_ratio = map.getEnemyDistanceRatio(enemy_id);
            if (enemy_type == ENEMY_DOG)
                audio_manager.displayDogGettingHit(distance_ratio);
            else
                audio_manager.displayHumanGettingHit(distance_ratio);
            return;
        }
        render_background_and_objects = false;
}

void InGameChangeProcessor::processPlayerHealthChange(int delta) {
    player.updateHealth(delta);
    if (delta < 0)
        audio_manager.displayPlayerLosingHealthSound();
    render_background_and_objects = false;
}

void InGameChangeProcessor::processEnemyRespawning(int enemy_id) {
    std::cout << "AUDIO PERRO\n";
    map.respawnPlayer(enemy_id);
    updateMandatoryRenderingTurns(ENEMY_DEATH_ANIMATION+1);
    int enemy_type = map.getEnemyTypeFromId(enemy_id);
    double distance_ratio = map.getEnemyDistanceRatio(enemy_id);
    std::cout << "PASO\n";
    if (enemy_type == ENEMY_DOG)
        audio_manager.displayDyingDog(1-distance_ratio);
    else
        audio_manager.displayDyingEnemy(1-distance_ratio);
}

void InGameChangeProcessor::processEnemyDying(int enemy_id) {
    map.killPlayer(enemy_id);
    int enemy_type = map.getEnemyTypeFromId(enemy_id);
    double distance_ratio = map.getEnemyDistanceRatio(enemy_id);
    if (enemy_type == ENEMY_DOG)
        audio_manager.displayDyingDog(1-distance_ratio);
    else
        audio_manager.displayDyingEnemy(1-distance_ratio);
    if (map.isLastPlayerStanding()) {
        audio_manager.playVictorySong();
        screen.displayVictoryScreen();
        game_over = true;
    }
    else
        updateMandatoryRenderingTurns(ENEMY_DEATH_ANIMATION+1);
}

void InGameChangeProcessor::processObjectRemoval(int object_id, int player_id) {
    int object_type = map.getObjectTypeFromId(object_id);
    map.removeObject(object_id);
    if (player_id != player.getId())
        return;
    if (ImageManager::objectIsAmmoRelated(object_type))
        audio_manager.playAmmoPickUpSound();
    else if (!ImageManager::objectIsWall(object_type))
        audio_manager.playItemPickUpSound();
    else if (ImageManager::objectIsDoor(object_type))
        audio_manager.playDoorOpeningSound();
    else
        audio_manager.displayFakeWallDisappearingSound();
}

void InGameChangeProcessor::updateMandatoryRenderingTurns(int new_value) {
    mandatory_rendering_turns = (new_value > mandatory_rendering_turns) ?
            new_value : mandatory_rendering_turns;
}
