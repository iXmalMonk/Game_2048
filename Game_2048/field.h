#ifndef _FIELD_H
#define _FIELD_H

#include "variables.h"

void createField(Game& game);

void printField(const Game& game);

void logicField(Game& game);

void drawField(Game& game);

void drawFieldBackground(Game& game);

void drawScore(Game& game);

void loadBestScore(Game& game);

void saveBestScore(Game& game);

void drawWin(const Game& game);

void drawLose(const Game& game);

void newGameDraw(const Game& game);

#endif