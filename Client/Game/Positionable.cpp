//
// Created by andy on 25/11/20.
//

#include "Positionable.h"

Positionable::Positionable(std::string name) : name(std::move(name)) {
}

std::string Positionable::getName() {
    return name;
}
