#pragma once

#include "../str.h"

extern const char ArrowActionType_setEnergy;
extern const char ArrowActionType_addInputEnergy;
extern const char ArrowActionType_removeInputEnergy;


#define ArrowActions_size 1+3+5+3+1
struct ArrowActions {
  // 000 00000
  //   #     
  //  ###
  // ##@##
  //  ###
  //   #
  char actions[1+3+5+3+1];
  // один ArrowsAction это 3 бита на тип экшена, 5 бит как параметр
  // ArrowActionType_setEnergy и 5 бит на то, какой теперь будет сигнал
};
struct ArrowEnvrioment {
  char energies[ArrowActions_size];
  char inputEnergy;
  // в кажом байте 5 бит отвечают за состояние 
  // 3 бита на клеточку свободны (потом можно будет использовать)
};

struct LogicArrow {
  struct Str arrowName;
  struct ArrowActions (*arrowLogic)(struct ArrowEnvrioment, char condition);
};

extern struct LogicArrow logicArrows[256];

struct LogicArrow* LogicArrows_get(struct Str arrowName);
void LogicArrows_reg(struct LogicArrow* LogicArrow);
void LogicArrows_init();
