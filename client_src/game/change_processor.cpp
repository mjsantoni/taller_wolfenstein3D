#include "client/game/change_processor.h"

#define MAX_CHANGES 100

/* Recibe lo necesario para poder aplicar los cambios sobre la vista.
 * Por ejemplo del lado del eventProcessor recibe el objeto Game y
 * el configHandler
 */
ChangeProcessor::ChangeProcessor(ClientMap& _map,
                                 ClientPlayer& _player,
                                 GameScreen& _screen,
                                 SharedQueue<Change>& _change_queue) :
                                 map(_map),
                                 player(_player),
                                 screen(_screen),
                                 change_queue(_change_queue),
                                 alive(true){
}

/* Ejecuta los cambios */
void ChangeProcessor::processChange(Change &change) {
    int change_id = change.change_id;
    int id = change.id;
    int value1 = change.value1;
    int value2 = change.value2;

    std::cout<< "Se procesa el cambio " << change_id << " con id " << id << " y valores " << value1 << " y " << value2 << std::endl;

    switch (change_id) {
        case (REMOVE_POSITIONABLE): {
            map.removeObject(id);
            // id: id del item
            break;
        }
        case (MOVE_PLAYER): {
            if (player.getId() == id)
                player.updatePosition(value1, value2);
            else
                map.moveObject(id, value1, value2);
            // id: player_id - value1: new_x - value2: new_y
            break;
        }
        case (CHANGE_POINTS): {
            if (player.getId() == id)
                player.updateScore(value1);
            // id: player_id - value1: points to add
            break;
        }
        case (CHANGE_HP): {
            if (player.getId() == id)
                player.updateHealth(value1);
            // id: player_id - value1: hp to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_hp del player
            break;
        }
        case (CHANGE_AMMO): {
            if (player.getId() == id)
                player.updateAmmo(value1);
            // id: player_id - value1: ammo to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_bullets del player
            break;
        }
        case (CHANGE_KEY): {
            if (player.getId() == id)
                player.updateKeys(value1);
            // id: player_id -> value1: cantidad (suma o resta keys)
            break;
        }
        case (KILL_PLAYER): {
            screen.renderDeadScreen();
            // id: player_id - Debe morir definitivamente
            break;
        }
        case (RESPAWN_PLAYER): {
            player.respawn();
            screen.renderRespawnScreen();
            // id: player_id - Debe morir y respawnear en su spawn original que tenes
            // deberia crear un dead body ahi tirado
            break;
        }
        case (ADD_PLAYER): {
            // id: player id asignado
            // habria que mandar el mapa completo aca
            break;
        }
        case (ADD_BULLETS_AT): {
            //map.addBulletsAt(id, value1, value2);
            // id: nuevo id_bullets - value1: new_x - value2: new_y
            break;
        }
        case (ADD_KEY_AT): {
            map.addObjectAt(id, ITEM_KEY, value1, value2);
            // id: nuevo id_key - value1: new_x - value2: new_y
            break;
        }
        case (ADD_MACHINE_GUN_AT): {
            map.addObjectAt(id, ITEM_MACHINE_GUN, value1, value2);
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_CHAIN_GUN_AT): {
            map.addObjectAt(id, ITEM_CHAIN_CANNON, value1, value2);
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_RPG_GUN_AT): {
            map.addObjectAt(id, ITEM_ROCKET_LAUNCHER, value1, value2);
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
            map.setRPGMissileExplosion(1, value1, value2);
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
        default: {
            break;
        }
    }
}

void ChangeProcessor::run() {
    while (alive) {
        Change change = change_queue.pop();
        if (change.isInvalid())
                continue;
        processChange(change);
    }
}

void ChangeProcessor::stop() {
    alive = false;
}

ChangeProcessor::~ChangeProcessor() {}

