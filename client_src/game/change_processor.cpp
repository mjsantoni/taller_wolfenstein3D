
#include "client/game/change_processor.h"

#define MAX_CHANGES 100

/* Recibe lo necesario para poder aplicar los cambios sobre la vista.
 * Por ejemplo del lado del eventProcessor recibe el objeto Game y
 * el configHandler
 */
ChangeProcessor::ChangeProcessor(ClientPlayer& _player,
                                 SharedQueue<Change>& _change_queue,
                                 std::atomic<bool>& _game_started,
                                 std::atomic<bool>& _player_ready) :
                                 screen(960, 600, map, player),
                                 player(_player),
                                 change_queue(_change_queue),
                                 alive(true),
                                 game_started(_game_started),
                                 player_ready(_player_ready),
                                 off_game_change_processor(game_started, map,
                                                         player, change_queue) {
}

/* Ejecuta los cambios */
void ChangeProcessor::processInGameChange(Change &change) {
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
            render_vector = std::vector<int>{1, 1, 0};
            // id: id del item
            break;
        }
        case (MOVE_PLAYER): {
            if (player.getId() == id) {
                std::cout << "El cliente se mueve en el mapa\n";
                player.updatePosition(value1, value2);
                render_vector = std::vector<int>{1, 1, 0};
            } else {
                std::cout << "Otro jugador se mueve en el mapa\n";
                map.moveObject(id, value1, value2);
                render_vector = std::vector<int>{0, 1, 0};
            }
            // id: player_id - value1: new_x - value2: new_y
            break;
        }
        case (CHANGE_POINTS): {
            if (player.getId() != id)
                break;
            player.updateScore(value1);
            render_vector = std::vector<int>{0, 0, 1};
            // id: player_id - value1: points to add
            break;
        }
        case (CHANGE_HP): {
            if (player.getId() != id)
                break;
            player.updateHealth(value1);
            render_vector = std::vector<int>{0, 0, 1};
            // id: player_id - value1: hp to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_hp del player
            break;
        }
        case (CHANGE_AMMO): {
            if (player.getId() != id)
                break;
            player.updateAmmo(value1);
            render_vector = std::vector<int>{0, 0, 1};
            // id: player_id - value1: ammo to change (puede ser + o -)
            // HUD: hay que verificar que no sobrepase el max_bullets del player
            break;
        }
        case (CHANGE_KEY): {
            if (player.getId() != id)
                break;
            player.updateKeys(value1);
            render_vector = std::vector<int>{0, 0, 1};
            // id: player_id -> value1: cantidad (suma o resta keys)
            break;
        }
        case (CHANGE_WEAPON): {
            if (player.getId() == id) {
                player.changeWeapon(value1);
                render_vector = std::vector<int>{0, 0, 1};
            }
            else {
                map.changeEnemyImage(id, value1);
                render_vector = std::vector<int>{0, 1, 0};
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
                map.erasePlayer(id);
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
            }
            // id: player_id - Debe morir y respawnear en su spawn original que tenes
            // deberia crear un dead body ahi tirado
            break;
        }
        case (ADD_PLAYER): {
            player.setId(id);
            std::pair<int, int> player_pos = map.getSpawnPositionForPlayer(id);
            player.setMapPosition(player_pos);
            std::cout << "Se ubica al jugador en la posicion (" << player_pos.first << "," << player_pos.second << ")\n";
            ready = true;
            std::cout << "Juego listo para iniciar\n";
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
            map.putObjectAt(id, ITEM_KEY, value1, value2);
            render_vector = std::vector<int>{0, 1, 0};
            // id: nuevo id_key - value1: new_x - value2: new_y
            break;
        }
        case (ADD_MACHINE_GUN_AT): {
            map.putObjectAt(id, ITEM_MACHINE_GUN, value1, value2);
            render_vector = std::vector<int>{0, 1, 0};
            // id: nuevo id_gun - value1: new_x - value2: new_y
            break;
        }
        case (ADD_CHAIN_GUN_AT): {
            map.putObjectAt(id, ITEM_CHAIN_CANNON, value1, value2);
            render_vector = std::vector<int>{0, 1, 0};
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
            render_vector = std::vector<int>{1, 0, 0};
            // id: new_item_id - value1: new_x - value2: new_y (viene de cerrar puerta)
            break;
        }
        case (RPG_MOVE_TO): {
            map.updateRPGMissile(id, value1, value2);
            render_vector = std::vector<int>{0, 1, 0};
            // id: mismo rpg_id - value1: new_x - value2: new_y (utilizar los viejos x,y para hacer la animacion)
            break;
        }
        case (RPG_EXPLODE_AT): {
            map.setRPGMissileExplosion(1, value1, value2);
            render_vector = std::vector<int>{0, 1, 0};
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
            render_vector = std::vector<int>{1, 1, 0};
            break;
        }
        case (CL_PLAYER_SHOOTING): {
            if (player.getAmmo() > 0 || player.getEquippedWeapon() == 1) {
                //audio_manager.displayPlayerAttackingSound(
                        //player.getEquippedWeapon());
                //screen.displayPlayerAttacking();
            } else {
                //audio_manager.displayEmptyGunSound();
            }
            return;
        }
        default: {
            break;
        }
    }
    std::cout << "pos del jugador: (" << player.getXPosition() << "," << player.getYPosition() << ")\n";
    screen.render(render_vector);
}

void ChangeProcessor::run() {
    event_handler.defineKeyScreenAreas(screen.getKeyScreenAreas());
    displayMenus();
    std::cout << "starting change processor\n";
    std::cout << "pos inicial del jugador: (" << player.getXPosition() << "," << player.getYPosition() << ")\n";
    screen.render(std::vector<int>{1, 1, 1});
    while (alive) {
        Change change = change_queue.pop();
        if (change.isInvalid()) {
            //std::cout << "invalid change\n";
                continue;
        }
        //std::cout << "El change processor recibe el cambio " << change.getChangeID() << std::endl;
        if (game_started) {
            map.updateEnemiesSprites();
            processInGameChange(change);
        }
    }
}

void ChangeProcessor::stop() {
    alive = false;
}

ChangeProcessor::~ChangeProcessor() {}

void ChangeProcessor::receiveIdsFromServer() {
    while(true) {
        Change change = change_queue.pop();
        if (change.getChangeID() != MAP_INITIALIZER)
            break;
        addMapChange(change);
    }
    std::cout << "Se termino de construir el mapa\n";
}

void ChangeProcessor::addMapChange(Change& change) {
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

void ChangeProcessor::displayMenus() {
    //audio_manager.playSong();
    displayIntro();
    std::cout << "Se inicia el juego" << std::endl;

    int game_mode = displayMatchModeMenu();
    if (game_mode != 1)
        return;
    displayLevelSelectionMenu();
    initializePlayer();
    initializeMap();
    displayLoadingScreen();
    sleep(1);
    //audio_manager.stopSong();
}

void ChangeProcessor::displayIntro() {
    screen.displayIntro();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            break;
    }
}

int ChangeProcessor::displayMatchModeMenu() {
    screen.displayMatchModeMenu();
    int ret_code = 0;
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        ret_code = event_handler.handleMatchModeScreenEvent(event);
        if (ret_code != 0)
            break;
    }
    return ret_code;
}

void ChangeProcessor::displayLevelSelectionMenu() {
    screen.displayLevelSelectionMenu();
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        int chosen_map = event_handler.handleLevelSelectionEvent(event);
        if (chosen_map != 0) {
            setMapPath(chosen_map);
            break;
        }
    }
}

void ChangeProcessor::displayLoadingScreen() {
    screen.displayLoadingScreen(true);
    while (true) {
        SDL_Delay(1);
        SDL_Event event;
        SDL_WaitEvent(&event);
        int player_is_ready = event_handler.handleLoadingScreenEvent(event);
        if (player_is_ready) {
            player_ready = true;
            break;
        }
    }
    while (!game_started) {
        screen.displayLoadingScreen(false);
        off_game_change_processor.processOffGameChanges();
    }
}

void ChangeProcessor::initializePlayer() {
    player_initializer.initializePlayer(player);
}

void ChangeProcessor::initializeMap() {
    MapParser map_parser(map_path);
    ClientMapGenerator::create(map, map_parser);
    //player.setMapPosition(std::pair<int, int>{128, 128});
    //map.putPlayerAt(std::pair<int, int>(128, 128));
}

void ChangeProcessor::setMapPath(int chosen_map) {
    map_path =  "../map.yaml";
}
