//
// Created by francisco on 11/2/21.
//

#ifndef TP_WOLFENSTEIN_CLIENT2_H
#define TP_WOLFENSTEIN_CLIENT2_H

#include "common/network_connection.h"
#include "common/network_error.h"
#include <iostream>

class Client2 {
    NetworkConnection sk;
    bool server_found = false;
    bool options_send = false;

public:
    Client2() : sk(-1) {}

    void lookForServer() {
        while (!server_found) {
                std::string host;
                std::string port;
                std::cout << "Ingrese el host del server: ";
                std::getline(std::cin, host);
                std::cout << "Ingrese el puerto del server: ";
                std::getline(std::cin, port);
              try {
                  NetworkConnection connection(host.c_str(),port.c_str());
                  sk = std::move(connection);
                  std::cout << "Conexion establecida correctamente\n";
                  server_found = true;
              } catch (const NetworkError& e) {
                  std::cerr << e.what();
              }
        }
    }

    [[noreturn]] void chooseActions() {
        while (true) {
            std::string data;
            std::cout << "Ingrese modo: 0 -> Create / 1 -> Join: ";
            std::getline(std::cin, data);
            sk.send_msg(data);
            if (data == "0") createNewGame();
            else if (data == "1") joinGame();
            else std::cout << "Pelotudo pone un numero bien una sola cosa te pido\n";
        }
    }

    void createNewGame() {
        while (true) {
            std::string data;
            std::cout << "Ingrese jugadores/bots/tiempo/id_mapa: ";
            std::getline(std::cin, data);
            sk.send_msg(data);

            std::string answer;
            sk.recv_msg(answer);
            std::cout << "Respuesta: " << answer << "\n";
            if (answer == "1\n") break;
        }
        /*
        while(true) {
            std::string answer;
            sk.recv_msg(answer);
            sleep(1);
        }*/
    }

    void joinGame() {
        while (true) {

            std::string games;
            sk.recv_msg(games);
            std::cout << "Los juegos disponibles son: " << games << "\n";

            std::string data;
            std::cout << "Ingrese el id del juego: ";
            std::getline(std::cin, data);
            sk.send_msg(data);

            std::string answer;
            sk.recv_msg(answer);
            std::cout << "Respuesta: " << answer << "\n";
            if (answer == "1\n") break;
        }
        /*
        while(true) {
            std::string answer;
            sk.recv_msg(answer);
            sleep(1);
        }*/
    }


};


#endif //TP_WOLFENSTEIN_CLIENT2_H
