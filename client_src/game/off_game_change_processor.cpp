//
// Created by andy on 8/2/21.
//

#include "client/game/off_game_change_processor.h"


OffGameChangeProcessor::OffGameChangeProcessor(ClientMap &_map,
                                            ClientPlayer &_player,
                                            SharedQueue<Change> &_change_queue,
                                            bool& _game_started,
                                            bool& _player_ready) :
                                            game_started(_game_started),
                                            player_ready(_player_ready),
                                            map(_map),
                                            player(_player),
                                            change_queue(_change_queue) {
}

void OffGameChangeProcessor::processOffGameChanges() {
    Change change = change_queue.pop();
    if (change.isInvalid())
        return;
    //std::cout << "Se procesa cambio previo al juego: " << change.getChangeID() << std::endl;
    int player_id = change.getPlayerID();
    switch (change.getChangeID()) {
        case MAP_INITIALIZER: {
            addMapChange(change);
            break;
        }
        case ADD_PLAYER: {
            player.setId(player_id);
            std::pair<int, int> player_pos =
                    map.getSpawnPositionForPlayer(player_id);
            player.setRespawningPosition(player_pos);
            player.setMapPosition(player_pos);
            player_ready = true;
        }
        case (TOTAL_PLAYERS_CONNECTED): {
            map.updateTotalPlayers(player_id); // el id es el numero de jugadores en realidad
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
        case (GAME_START): {
            std::cout << "Se recibe cambio para iniciar el juego\n";
            map.addEnemies(player.getId());
            game_started = true;
            // id: mismo rpg_id - value1: new_x - value2: new_y (explota en esa x,y)
            break;
        }
    }
}

void OffGameChangeProcessor::addMapChange(Change& change) {
    int object_id = change.getPlayerID();
    int x_pos = change.getFirstValue();
    int y_pos = change.getSecondValue();
    map.addObjectId(object_id, x_pos, y_pos);
}


