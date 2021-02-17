//
// Created by andy on 5/2/21.
//

#include "client/communication/change_factory.h"

#include <string>

#define CHANGE_ID 0
#define ID 1
#define VALUE_1 2
#define VALUE_2 3

ChangeFactory::ChangeFactory(SharedQueue<Change>& _change_queue) :
        change_queue(_change_queue) {}

Change ChangeFactory::createFromBytes(char* bytes) {
    std::vector<int> buffer;
    std::stringstream ss(bytes);
    std::string s;
    while (std::getline(ss, s, '/')) {
        if (s.size() == 0) continue;
        buffer.push_back(std::stoi(s));
    }
    Change change(buffer[CHANGE_ID], buffer[ID], buffer[VALUE_1],
                  buffer[VALUE_2]);
    return change;
    //std::cout << "El cliente pushea a la cola de cambios el cambio " << change.getChangeID() << std::endl;
}

/* test only */