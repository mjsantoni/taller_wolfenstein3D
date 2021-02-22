//
// Created by andy on 18/2/21.
//

#include "client/game/effects_handler.h"

int EffectsHandler::getIdForEffect() {
  int current_counter = id_counter;
  --id_counter;
  return current_counter;
}
