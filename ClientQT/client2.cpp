#include "clientQT/client2.h"

Client2::Client2() : sk(-1) {}

void Client2::lookForServer() {
    while (!server_found) {
        // std::string portLine;
        // std::cout << "Ingrese el hostLine del server: ";
        // std::getline(std::cin, hostLine);
        // std::cout << "Ingrese el puerto del server: ";
        // std::getline(std::cin, portLine);
        // try {
        //     NetworkConnection connection(hostLine.c_str(), portLine.c_str());
        //     sk = std::move(connection);
        //     std::cout << "Conexion establecida correctamente\n";
        //     server_found = true;
        // } catch (const NetworkError& e) {
        //     std::cerr << e.what();
        // }
    }
}

void Client2::chooseActions() {
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

void Client2::createNewGame() {
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

void Client2::joinGame() {
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