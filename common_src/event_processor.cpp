#include "common/event_processor.h"
#include "common/hit_handler.h"
/*
EventProcessor::EventProcessor(Game &_game) : game(_game) {}

std::vector<Change> EventProcessor::process(Event& event) {
    int id = event.event_id;
    int player_id = event.player_id;
    int value = event.value;
    std::vector<Change> changes;

    switch (id) {
        case (CONNECT_PLAYER): {
            int id_new_player = game.connectPlayer();
            changes.push_back(Change(ADD_PLAYER, id_new_player, -1, -1, true));
            // Falta evento de enviar el mapa entero al conectarse
            break;
        }
        case (MOVE_PLAYER): {
            std::cout << "Muevo player!\n";
            std::pair<Coordinate,
                    std::vector<Positionable>> move_changes = game.movePlayer(player_id);
            changes.push_back(Change(MOVE_PLAYER, player_id,
                                     move_changes.first.x, move_changes.first.y, true));
            for (auto &item : move_changes.second) {
                changes.push_back(Change(REMOVE_POSITIONABLE, item.getId(), -1, -1, true));
                changes.push_back(Change(CHANGE_POINTS, player_id, 999, -1, false));
                // Reemplazar el 999 por configParser.getPoints(item);
            }
            break;
        }
        case (SHOOT): {
            Hit hit_event = game.shoot(player_id);
            HitHandler hit_handler;
            hit_handler.processHit(hit_event, changes);
            break;
        }
        case (OPEN_DOOR): {
            // Deberia hacer un chequeo si tiene paredes alrededor el cliente
            // antes de mandar el evento (para no gastar mucho recurso)
            std::pair<Coordinate, int> opened_door = game.openDoor(player_id);
            if (!opened_door.first.isValid()) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, -1, opened_door.first.x,
                                     opened_door.first.y, true));
            if (opened_door.second != -1) {
                changes.push_back(Change(PLAYER_USE_KEY, player_id, opened_door.second,
                                         -1, false));
            }
            break;
        }
        case (PUSH_WALL): {
            // Deberia hacer un chequeo si tiene paredes alrededor el cliente
            // antes de mandar el evento (para no gastar mucho recurso)
            Coordinate pushed_wall = game.pushWall(player_id);
            if (!pushed_wall.isValid()) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, -1, pushed_wall.x, pushed_wall.y, true));
            break;
        }
        case (TURN_CAMERA): {
            // por ahora los demas no ven el cambio de angulo del resto
            // POR AHORA ES ASINCROCNICO, HACEMOS LA MISMA SUMA EN EL CLIENTE Y SV
            game.rotate(player_id, value);
            break;
        }
        case (CHANGE_GUN): {
            // El cliente debe verificar que pueda cambiar a esa arma antes de crear el evento
            game.changeGun(player_id, value); // value == hotkey
            changes.push_back(Change(CHANGE_WEAPON, player_id, value, -1, true));
        }
        default: {
            break;
        }
    }
    return changes;
}
*/