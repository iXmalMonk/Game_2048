#ifndef _SECONDARY_H
#define _SECONDARY_H

#include "variables.h"

void init(Game& game);

void deInit(Game& game, int error);

void hideConsole(bool flag);

void printValue(const Game& game, int value, int x, int y, int size);

#endif