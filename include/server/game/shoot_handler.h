#ifndef TP_WOLFENSTEIN_SHOOT_HANDLER_H
#define TP_WOLFENSTEIN_SHOOT_HANDLER_H

#include "server/game/map.h"
#include "server/game/hit.h"
#include "server/entities/rpg.h"
#include "server/game/damage_calculator.h"
#include "common/change.h"
#include "server/game/score_handler.h"

class ShootHandler {
private:
    Map& map;
    std::map<int, RPG> rpgs;
    DamageCalculator dmg_calculator;
    ScoreHandler& scoreHandler;

    /* Ejecuta la accion de hacer y recibir el disparo, recibe el que disparo, a quien disparo, cuanta vida le saco */
    int hit(Player &player, Player &enemy, int damage, bool &enemy_dies);

    /* Dada una posicion y el angulo, obtiene las N posiciones adyacentes */
    std::vector<Coordinate> getAdjacents(Coordinate &pos, double angle, int adj_units_to_check);

public:

    /* Recibe un mapa por referencia y un scorehandler para cargar los resultados */
    ShootHandler(Map& _map, ScoreHandler& _sh) : map(_map), scoreHandler(_sh) {}

    /* Ejecuta un disparo del player con su angulo. Ademas recibe todos los otros players del juego.
     * Devuelve un Hit (clase que encapsula lo ocurrido durante el disparo y un vector de cambios. */
    std::pair<Hit, std::vector<Change>> shoot(Player& player, double angle, std::vector<Player>& players);


    bool hitAtPos(std::vector<Coordinate>& positions, std::vector<Player>& players, Player& player,
                  std::vector<std::pair<int, int>>& enemy_dmg_done, int pos_travelled,
                  bool is_adjacent);

    /* Dada una cordenada y cuantas posiciones a revisar, devuelve los ids de todos los players dentro del area. */
    std::vector<int> playersInArea(Coordinate &coord, int units, int id);


    /* Simula el disparo de un arma tradicional, se entiende por arma tradicional a cualquier arma diferente al RPG. */
    Hit shootRegularGun(int bullets_to_shoot, Player &player, std::vector<Coordinate> &straight_line,
                        std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players);

    /* Recibe una lista de id de players alcanzados, quien disparo, la coordenada de explosion, un vector para cargar el daño hecho a cada
     * jugador y la lista de jugadores. Calcula para cada jugador alcanzado por el RPG el daño que recibira. */
    void
    hitPlayersWithRPG(std::vector<int> &players_found, Player &player, Coordinate explosion_center,
                      std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players);

    /* Simula el disparo de un RPG y devuelve el Hit asociado. */
    Hit shootRPG(int bullets_to_shoot, Player &player, std::vector<Coordinate> straight_line,
                 std::vector<std::pair<int, int>> &enemy_dmg_done, std::vector<Player> &players,
                 std::vector<Change> &changes);

    /* Avanza un RPG por su camino. Aplicando la logica de explosion y actualizando sus datos. */
    Hit travelAndExplodeRPG(RPG &rpg, int bullets_to_shoot, std::vector<std::pair<int, int>> &enemy_dmg_done,
                            std::vector<Player> &players);

    /* Actualiza todos los RPG que se encuentran en vuelo en el momento. Devuelve un Hit con la informacion. */
    Hit travelAndExplodeAllRPGS(std::vector<Player> &players, std::vector<Change> &changes);
};


#endif //TP_WOLFENSTEIN_SHOOT_HANDLER_H
