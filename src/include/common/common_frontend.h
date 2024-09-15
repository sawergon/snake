//
// Created by Kimiko Dornish on 9/12/24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_COMMON_FRONTEND_H
#define CPP3_BRICKGAME_V2_0_1_COMMON_FRONTEND_H

#include "ncurses.h"
#include "brick_game_types.h"

#define KEY_ACTION 32
#define KEY_QUIT 113
#define KEY_START 10

void displayStartMessage(char** games_list, int amount);

int chooseGame(int amount);

void displayStartMessageGame(char *game_name);

void displayEndMessageGame(int score, char *game_name);

void displayErrorMessage();

void displayHoldMessage();

void displaySureEndGameMessage();

bool getStartCommand();

void printRectangle(int top_y, int bottom_y, int left_x, int right_x);

UserAction_t getAction();

#endif //CPP3_BRICKGAME_V2_0_1_COMMON_FRONTEND_H
