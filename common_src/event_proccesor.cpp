#include "common/event_proccesor.h"

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
            changes.push_back(Change(ADD_PLAYER, 000, id_new_player, 000, true));
            break;

        case (MOVE_PLAYER):
            std::pair<Coordinate,
                    std::vector<Positionable>> move_changes = game.movePlayer(player_id);
            changes.push_back(Change(MOVE_PLAYER, player_id, position.x, position.y, true));
            for (auto& item : move_changes.second) {
                changes.push_back(Change(REMOVE_POSITIONABLE, ....))
            }
            break;

        case (SHOOT):
            Hit hit_event = game.shoot();
            HitHandler hit_handler;
            hit_handler.processHit(hit_event, changes);
            //lo de abajo no iria
            for (each shoot) {
                changes.push_back(Change(CHANGE_AMMO, player_id, balas_gastadas, false));
                changes.push_back(Change(CHANGE_HP, cada
                shoot.enemy, daño
                q
                come, 0, false));
                // Si detecto que el daño recibido es -1, entonces:
                // changes.push_back(Change(PLAYER_DEATH, player_id,0,0,0)
                // changes.push_back(Change(PLAYER_RESPAWN, ....)
            }

        case (OPEN_DOOR):
            Coordinate opened_door = game.openDoor(player_id);
            if (opened_door.x == -1 || opened_door.y == -1) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, 9999999, opened_door.x, opened_door.y, true));

        case (PUSH_WALL):
            Coordinate pushed_wall = game.pushWall(player_id);
            if (pushed_wall.x == -1 || pushed_wall.y == -1) break;
            changes.push_back(Change(REMOVE_POSITIONABLE, 9999999, pushed_wall.x, pushed_wall.y, true));

        case (TURN_CAMERA):
            // por ahora los demas no ven el cambio de angulo del resto
            // POR AHORA ES ASINCROCNICO, HACEMOS LA MISMA SUMA EN EL CLIENTE Y SV
            game.rotate(player_id, value);
            break;

        case (CHANGE_GUN):
            // El cliente debe verificar que pueda cambiar a esa arma antes de crear el evento
            game.changePlayerGun(player_id, value);
            changes.push_back(Change(CHANGE_WEAPON, player_id, 0, 0, true));
    }

}
*/