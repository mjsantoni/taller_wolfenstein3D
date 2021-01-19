#include "common/event_proccesor.h"
#include "common/hit_handler.h"

EventProccesor::EventProccesor(Game& _game, EventQueue &_eq) : game(_game), eq(_eq) {}
/*
std::vector<Change> EventProccesor::process(Event& event) {
    int id = event.id;
    int player_id = event.player_id;
    int value = event.value;
    std::vector<Change> changes;

    switch (id) {
        case (CONNECT_PLAYER):
            int id_new_player = game.connectPlayer();
            changes.push_back(Change(ADD_PLAYER, id_new_player, -1, -1, true));
            break;

        case (MOVE_PLAYER):
            std::pair<Coordinate,
                    std::vector<Positionable>> move_changes = game.movePlayer(player_id);
            changes.push_back(Change(MOVE_PLAYER, player_id,
                                     move_changes.first.x, move_changes.first.y, true));
            for (auto& item : move_changes.second) {
                changes.push_back(Change(REMOVE_POSITIONABLE, -1, item.getId(), -1, true));
            }
            break;

        case (SHOOT):
            Hit hit_event = game.shoot(player_id);
            HitHandler hit_handler;
            hit_handler.processHit(hit_event, changes);
            break;

        case (OPEN_DOOR):
            Coordinate opened_door = game.openDoor(player_id);
            if (opened_door.x == -1 || opened_door.y == -1) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, -1, opened_door.x, opened_door.y, true));

        case (PUSH_WALL):
            Coordinate pushed_wall = game.pushWall(player_id);
            if (pushed_wall.x == -1 || pushed_wall.y == -1) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, -1, pushed_wall.x, pushed_wall.y, true));

        case (TURN_CAMERA):
            // por ahora los demas no ven el cambio de angulo del resto
            // POR AHORA ES ASINCROCNICO, HACEMOS LA MISMA SUMA EN EL CLIENTE Y SV
            game.rotate(player_id, value);
            break;

        case (CHANGE_GUN):
            // El cliente debe verificar que pueda cambiar a esa arma antes de crear el evento
            game.changeGun(player_id, value); // value == hotkey
            changes.push_back(Change(CHANGE_WEAPON, player_id, -1, -1, true));
    }
*/
}
