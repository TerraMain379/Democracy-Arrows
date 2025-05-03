#include "./logicarrows.h"

#include <stdlib.h>

const char ArrowActionType_setEnergy = 1;
const char ArrowActionType_addInputEnergy = 2;
const char ArrowActionType_removeInputEnergy = 3;

int size;
struct LogicArrow logicArrows[256];

struct LogicArrow* LogicArrows_get(struct Str arrowName) {
  for (int i = 0; i < size; i++) {
    struct LogicArrow* logicArrow = &logicArrows[i];
    if (Str_equals(arrowName, logicArrow->arrowName)) {
      return logicArrow;
    }
  }
  return 0;
}
void LogicArrows_reg(struct LogicArrow* logicArrow) {
  if (size == 256) {
    perror("Out of bounds error: You can't register 256 arrows!");
    exit(-1);
  }
  logicArrows[size] = *logicArrows;
  size++;
}

char genAction(char actionType, char actionValue) {
  if (actionType > 0b00000111) {
    perror("ERROR [logicarrows.h:genAction]: actionType out of bounds ( > 0b00000111)");
  }
  if (actionType > 0b00011111) {
    perror("ERROR [logicarrows.h:genAction]: actionValue out of bounds ( > 0b00011111)");
  }
  return actionType + (actionValue << 3);
}

struct ArrowActions _logic_arrow(struct ArrowEnvrioment env, char condition) {
  struct ArrowActions arrowActions = {0};
  if (env.inputEnergy == 0) {
    arrowActions.actions[6] = genAction(ArrowActionType_setEnergy, 0);
  }
  else {
    arrowActions.actions[6] = genAction(ArrowActionType_setEnergy, 1);
  }

  char rotation = condition & 0b00000011;
  if (env.energies[6] == 1) {
    char action = genAction(ArrowActionType_addInputEnergy, 1);
    if (rotation==0) {
      arrowActions.actions[2] = action;
    }
    else if (rotation==1) {
      arrowActions.actions[7] = action;
    }
    else if (rotation==2) {
      arrowActions.actions[10] = action;
    }
    else if (rotation==3) {
      arrowActions.actions[5] = action;
    }
  }
  return arrowActions;
}
struct ArrowActions _logic_source(struct ArrowEnvrioment env, char condition) {
  struct ArrowActions arrowActions = {0};
  char action = genAction(ArrowActionType_addInputEnergy, 1);
  arrowActions.actions[2] = action;
  arrowActions.actions[7] = action;
  arrowActions.actions[10] = action;
  arrowActions.actions[5] = action;
  return arrowActions;
}
struct ArrowActions _logic_blocker(struct ArrowEnvrioment env, char condition) {
  struct ArrowActions arrowActions = {0};
  if (env.inputEnergy == 0) {
    arrowActions.actions[6] = genAction(ArrowActionType_setEnergy, 0);
  }
  else {
    arrowActions.actions[6] = genAction(ArrowActionType_setEnergy, 1);
  }

  char rotation = condition & 0b00000011;
  if (env.energies[6] == 1) {
    char action = genAction(ArrowActionType_setEnergy, 0);
    if (rotation==0) {
      arrowActions.actions[2] = action;
    }
    else if (rotation==1) {
      arrowActions.actions[7] = action;
    }
    else if (rotation==2) {
      arrowActions.actions[10] = action;
    }
    else if (rotation==3) {
      arrowActions.actions[5] = action;
    }
  }
  return arrowActions;
}

void LogicArrows_init() {
  struct LogicArrow logicArrow;

  logicArrow.arrowName = Str_new("arrows:arrow");
  logicArrow.arrowLogic = _logic_arrow;
  LogicArrows_reg(&logicArrow);

  logicArrow.arrowName = Str_new("arrows:source");
  logicArrow.arrowLogic = _logic_source;
  LogicArrows_reg(&logicArrow);

  logicArrow.arrowName = Str_new("arrows:blocker");
  logicArrow.arrowLogic = _logic_blocker;
  LogicArrows_reg(&logicArrow);
}
