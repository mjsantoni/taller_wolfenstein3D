#include "common/change_processor.h"

/* Recibe lo necesario para poder aplicar los cambios sobre la vista.
 * Por ejemplo del lado del eventProcessor recibe el objeto Game y
 * el configHandler
 */
ChangeProcessor::ChangeProcessor() {

}

/* Ejecuta los cambios */
void ChangeProcessor::process(Change &change) {
    int change_id = change.change_id;
    int id = change.id;
    int value1 = change.value1;
    int value2 = change.value2;

    switch (change_id) {
        case (REMOVE_POSITIONABLE): {
            // id: id del item
            break;
        }
        case (MOVE_PLAYER): {
            // id: player_id - value1: new_x - value2: new_y
            break;
        }
        case (CHANGE_POINTS): {
            // id: player_id - value1: points to add
            break;
        }
        case (CHANGE_HP): {
            // id: player_id - value1: hp to change (puede ser + o -)
            break;
        }
        case (CHANGE_AMMO): {
            // id: player_id - value1: ammo to change (puede ser + o -)
            break;
        }
        case (KILL_PLAYER): {
            // id: player_id - Debe morir definitivamente
            break;
        }
        case (RESPAWN_PLAYER): {
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
            // id: nuevo id_bullets - value1: new_x - value2: new_y
            break;
        }
        case (ADD_KEY_AT): {
            // id: nuevo id_key - value1: new_x - value2: new_y
            break;
        }
        case (ADD_MACHINE_GUN_AT): {
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_CHAIN_GUN_AT): {
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_RPG_GUN_AT): {
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (PLAYER_USE_KEY): {
            // id: player_id -> restarle en el hud una llave
            break;
        }
        case (ADD_UNLOCKED_DOOR): {
            // id: new_item_id - value1: new_x - value2: new_y (viene de cerrar puerta)
            break;
        }
        case (RPG_MOVE_TO): {
            // id: mismo rpg_id - value1: new_x - value2: new_y (utilizar los viejos x,y para hacer la animacion)
            break;
        }
        case (RPG_EXPLODE_AT): {
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
        default: {
            break;
        }
    }
}
