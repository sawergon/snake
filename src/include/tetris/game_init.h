//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_GAME_INIT_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_GAME_INIT_H_

#include "../common/brick_game_types.h"
#include "../common/score_work.h"
#include "matrix_work.h"
#define GAME_TETRIS_HIGH_SCORE_FILE "tetris_high_score.txt"
/**
 * @addtogroup GameInit Инициализация игры
 * @{
 */
/**
 * Функция создания игры.
 * Происходит инициализация объекта нулевыми значениями, поэтому после следует
 * вызвать функцию `initGame`
 * @return созданная игра
 * @warning требуется вызов функции `initGame` для инициализации игры
 */
GameInfo_t *createGame();

/**
 * Функция инициализации игры.
 * @param game игра
 * @warning требуется вызов функции `createGame` перед вызовом функции
 */
void initGame(GameInfo_t *game,const char *filename);

/**
 * Получение текущей игровой информации
 * @return игровая информация
 */
GameInfo_t *getGameState();
/// @}

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_GAME_INIT_H_
