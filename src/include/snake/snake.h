//
// Created by Kimiko Dornish on 9/12/24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SNAKE_WRAPPER_H
#define CPP3_BRICKGAME_V2_0_1_SNAKE_WRAPPER_H


#include "../common/brick_game_types.h"
#include "stdbool.h"
/**
 * Функция для обработки пользовательского ввода
 * @param action действие пользователя
 * @param hold зажатие клавиши
 */
void userInputSnake(UserAction_t action, bool hold);

/**
 * Функция для обновления текущей игровой информации
 * @return текущая игровая информация
 */
GameInfo_t updateCurrentStateSnake();

FiniteMachineStatus_t* getMachineStatusSnake();

void startNewGameSnake();

#endif //CPP3_BRICKGAME_V2_0_1_SNAKE_WRAPPER_H
