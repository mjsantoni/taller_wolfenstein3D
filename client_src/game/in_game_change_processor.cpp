
#include "client/game/in_game_change_processor.h"

#define MAX_CHANGES 5
#define MAX_ITERATIONS 25

/* Recibe lo necesario para poder aplicar los cambios sobre la vista.
 * Por ejemplo del lado del eventProcessor recibe el objeto Game y
 * el configHandler
 */
InGameChangeProcessor::InGameChangeProcessor(GameScreen& _screen,
                                             ClientMap& _map,
                                             ClientPlayer& _player,
                                             SharedQueue<Change>& _change_queue,
                                             AudioManager& _audio_manager) :
                                 screen(_screen),
                                 map(_map),
                                 player(_player),
                                 change_queue(_change_queue),
                                 alive(true),
                                 audio_manager(_audio_manager) {
}

/* Ejecuta los cambios */
std::vector<int> InGameChangeProcessor::processInGameChange(Change &change) {
    if (change.isInvalid())
        return std::vector<int>{0, 0, 0, 0};
    int change_id = change.change_id;
    int id = change.id;
    int value1 = change.value1;
    int value2 = change.value2;

    std::cout<< "Se procesa el cambio " << change_id << " con id " << id << " y valores " << value1 << " y " << value2 << std::endl;
    // render ray_caster, render object_drawer, render ui_drawer
    std::vector<int> render_vector{0, 0, 0};
    switch (change_id) {
        case (REMOVE_POSITIONABLE): {
            map.removeObject(id);
            render_vector = std::vector<int>{1, 1, 1, 0};
            // id: id del item
            break;
        }
        case (MOVE_PLAYER): {
            if (player.getId() == id) {
                std::cout << "El cliente se mueve en el mapa\n";
                player.updatePosition(value1, value2);
                render_vector = std::vector<int>{1, 1, 1, 0};
            } else {
                std::cout << "Otro jugador se mueve en el mapa\n";
                map.moveObject(id, value1, value2);
                render_vector = std::vector<int>{0, 1, 0, 0};
            }
            // id: player_id - value1: new_x - value2: new_y
            break;
        }
        case (CHANGE_POINTS): {
            if (player.getId() != id)
                break;
            player.updateScore(value1);
            render_vector = std::vector<int>{0, 0, 0, 1};
            // id: player_id - value1: points to add
            break;
        }
        case (CHANGE_HP): {
            if (player.getId() != id)
                break;
            player.updateHealth(value1);
            render_vector = std::vector<int>{0, 0, 0, 1};
            // id: player_id - value1: hp to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_hp del player
            break;
        }
        case (CHANGE_AMMO): {
            int ammo_delta = value1;
            if (player.getId() != id) {
                if (ammo_delta > 0)
                    break;
                map.setEnemyAttacking(id);
                audio_manager.displayEnemyShot();
            }
            if (ammo_delta < 0) {
                audio_manager.displayPlayerAttackingSound(player.
                                                          getEquippedWeapon());
                screen.displayPlayerAttacking();
                render_vector = std::vector<int>{0, 0, 1, 1};
            }
            else if (ammo_delta == 0) {
                if (player.getEquippedWeapon() != 1) {
                    audio_manager.displayEmptyGunSound();
                    render_vector = std::vector<int>{0, 0, 0, 0};
                }
                else {
                    audio_manager.displayPlayerAttackingSound(1);
                    render_vector = std::vector<int>{1, 1, 1, 0};
                }
            }
            player.updateAmmo(value1);
            // id: player_id - value1: ammo to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_bullets del player
            break;
        }
        case (CHANGE_KEY): {
            if (player.getId() != id)
                break;
            player.updateKeys(value1);
            render_vector = std::vector<int>{0, 0, 0, 1};
            // id: player_id -> value1: cantidad (suma o resta keys)
            break;
        }
        case (CHANGE_WEAPON): {
            if (player.getId() == id) {
                player.changeWeapon(value1);
                render_vector = std::vector<int>{0, 0, 1, 1};
            }
            else {
                map.changeEnemyImage(id, value1);
                render_vector = std::vector<int>{0, 1, 0, 0};
            }
            // id: player_id -> value1: cantidad (suma o resta keys)
            break;
        }
        case (KILL_PLAYER): {
            if (player.getId() == id) {
                while (true)
                    screen.displayDeadScreen();
                //algo mas aca seguro
            } else {
                map.killPlayer(id);
                audio_manager.displayDyingEnemy();
            }
            // id: player_id - Debe morir definitivamente
            break;
        }
        case (RESPAWN_PLAYER): {
            std::cout << "RESPAWNING\n";
            if (player.getId() == id) {
                player.respawn();
                screen.displayRespawningScreen();
                sleep(2);
            } else {
                map.respawnPlayer(id);
                audio_manager.displayDyingEnemy();
            }
            // id: player_id - Debe morir y respawnear en su spawn original que tenes
            // deberia crear un dead body ahi tirado
            break;
        }
        case (ADD_PLAYER): {
            player.setId(id);
            std::pair<int, int> player_pos = map.getSpawnPositionForPlayer(id);
            player.setMapPosition(player_pos);
            //std::cout << "Se ubica al jugador en la posicion (" << player_pos.first << "," << player_pos.second << ")\n";
            //std::cout << "Juego listo para iniciar\n";
            // id: player id asignado
            // habria que mandar el mapa completo aca
            break;
        }
        case (ADD_BULLETS_AT): {
            map.putObjectAt(id, ITEM_BULLETS, value1, value2);
            // id: nuevo id_bullets - value1: new_x - value2: new_y
            render_vector = std::vector<int>{0, 1, 1, 0};
            break;
        }
        case (ADD_KEY_AT): {
            map.putObjectAt(id, ITEM_KEY, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            // id: nuevo id_key - value1: new_x - value2: new_y
            break;
        }
        case (ADD_MACHINE_GUN_AT): {
            map.putObjectAt(id, ITEM_MACHINE_GUN, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_CHAIN_GUN_AT): {
            map.putObjectAt(id, ITEM_CHAIN_CANNON, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_RPG_GUN_AT): {
            map.putObjectAt(id, ITEM_ROCKET_LAUNCHER, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_UNLOCKED_DOOR): {
            map.updateUnlockedDoor(id, value1, value2);
            render_vector = std::vector<int>{1, 1, 1, 0};
            // id: new_item_id - value1: new_x - value2: new_y (viene de cerrar puerta)
            break;
        }
        case (RPG_MOVE_TO): {
            map.updateRPGMissile(id, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            // id: mismo rpg_id - value1: new_x - value2: new_y (utilizar los viejos x,y para hacer la animacion)
            break;
        }
        case (RPG_EXPLODE_AT): {
            map.setRPGMissileExplosion(id, value1, value2);
            render_vector = std::vector<int>{0, 1, 1, 0};
            audio_manager.displayExplosionSound();
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
            render_vector = std::vector<int>{1, 1, 1, 0};
            break;
        }
        default: {
            break;
        }
    }
    std::cout << "pos del jugador: (" << player.getXPosition() << "," << player.getYPosition() << ")\n";
    return render_vector;
}

void InGameChangeProcessor::processInGameChanges() {
    Change change = change_queue.pop();
    std::vector<int> render_vector = processInGameChange(change);
    screen.render(render_vector);
    map.updateEnemiesSprites();
    if (map.updateEvents()) {
        usleep(300000);
        screen.render(std::vector<int>{1, 1, 1, 0});
    }
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
    alive = false;
}

void InGameChangeProcessor::receiveIdsFromServer() {
    while(true) {
        Change change = change_queue.pop();
        if (change.getChangeID() != MAP_INITIALIZER)
            break;
        addMapChange(change);
    }
    std::cout << "Se termino de construir el mapa\n";
}

void InGameChangeProcessor::addMapChange(Change& change) {
    /*
    int object_id = change.getPlayerID();
    int x_pos = change.getFirstValue();
    int y_pos = change.getSecondValue();
    if (isWall(object_id)) {
        std::pair<int, int> grid =
                Calculator::calculateGrid(map.getGridSize(), x_pos, y_pos);
        map.putDrawableAt(grid, object_id);
    }
     */
}




