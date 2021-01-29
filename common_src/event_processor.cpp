#include "common/event_processor.h"
#include "server/events/hit_handler.h"
/*
EventProcessor::EventProcessor(Game &_game, std::string config_path) :
                              game(_game), configParser(config_path) {}

std::vector<Change> EventProcessor::process(Event& event) {
    int id = event.event_id;
    int player_id = event.player_id;
    int value = event.value;
    std::vector<Change> changes;

    switch (id) {
        case (CONNECT_PLAYER): {
            int id_new_player = game.connectPlayer();
            changes.emplace_back(ADD_PLAYER, id_new_player, INVALID, INVALID, true);
            // Falta evento de enviar el mapa entero al conectarse
            break;
        }
        case (MOVE_PLAYER): {
            std::cout << "MUEVO PLAYER!\n";
            movePlayer(player_id, value, changes);
            break;
        }
        case (SHOOT): {
            std::cout << "DISPARO!\n";
            std::pair<Hit, std::vector<Change>> hit_event = game.shoot(player_id);
            for (auto& change : hit_event.second) changes.push_back(change);

            HitHandler hit_handler;
            hit_handler.processHit(hit_event.first, changes, game.getPlayersAlive());
            break;
        }
        case (OPEN_DOOR): {
            std::cout << "INTENTO ABRIR PUERTA!\n";
            // Deberia hacer un chequeo si tiene paredes alrededor el cliente
            // antes de mandar el evento (para no gastar mucho recurso)
            std::pair<bool,int> opened_door = game.openDoor(player_id);
            bool use_key = opened_door.first;
            int door_id = opened_door.second;

            if (door_id == -1) break;

            changes.emplace_back(REMOVE_POSITIONABLE, door_id, INVALID, INVALID, true);
            if (use_key)
                changes.emplace_back(CHANGE_KEY, player_id, INVALID,INVALID, false);
            break;
        }
        case (PUSH_WALL): {
            std::cout << "PUSH WALL!\n";
            // Deberia hacer un chequeo si tiene paredes alrededor el cliente
            // antes de mandar el evento (para no gastar mucho recurso)
            int pushed_wall_id = game.pushWall(player_id);
            if (pushed_wall_id == -1) break;
            changes.emplace_back(REMOVE_POSITIONABLE, pushed_wall_id, INVALID, INVALID, true);
            break;
        }
        case (TURN_CAMERA): {
            std::cout << "TURN CAMERA!\n";
            // por ahora los demas no ven el cambio de angulo del resto
            // POR AHORA ES ASINCROCNICO, HACEMOS LA MISMA SUMA EN EL CLIENTE Y SV
            game.rotate(player_id, value);
            break;
        }
        case (CHANGE_GUN): {
            std::cout << "CHANGE GUN!\n";
            // El cliente debe verificar que pueda cambiar a esa arma antes de crear el evento
            game.changeGun(player_id, value); // value == hotkey
            changes.emplace_back(CHANGE_WEAPON, player_id, value, INVALID, true);
            break;
        }
        case (PLAYER_READY): {
            game.playerIsReady(event.getPlayerID());
        }
        default: {
            break;
        }
    }
    return changes;
}

void EventProcessor::movePlayer(int player_id, int value, std::vector<Change> &changes) {
    std::pair<Coordinate,
            std::vector<Positionable>> move_changes = game.movePlayer(player_id);
    changes.emplace_back(MOVE_PLAYER, player_id,
                         move_changes.first.x, move_changes.first.y, true);
    for (auto &item : move_changes.second) {
        changes.emplace_back(REMOVE_POSITIONABLE, item.getId(), INVALID, INVALID, true);

        if (item.getCategory() == "treasure")  {
            changes.emplace_back(CHANGE_POINTS, player_id,
                                 configParser.getSpecificCategory(item.getCategory(), item.getType()),
                                 INVALID, false);
        }
        else if (item.getCategory() == "hp_item")  {
            changes.emplace_back(CHANGE_HP, player_id,
                                 configParser.getSpecificCategory(item.getCategory(), item.getType()),
                                 INVALID, false);
        }
        // MOSTRAMOS EN EL HUD LAS ARMAS QUE TIENE????????????!?!!?!?!?!?!?
        else if (item.getCategory() == "gun")  {
            changes.emplace_back(ADD_GUN_TO_PLAYER, player_id,
                                 configParser.getSpecificCategory(item.getCategory(), item.getType()),
                                 -1, false);
        }
        else if (item.getCategory() == "bullets")  {
            changes.emplace_back(CHANGE_AMMO, player_id,
                                 configParser.getSpecificCategory(item.getCategory(), item.getType()),
                                 INVALID, false);
        }
        else if (item.getCategory() == "key")  {
            changes.emplace_back(CHANGE_KEY, player_id, 1, INVALID, false);
        }
    }
}
*/