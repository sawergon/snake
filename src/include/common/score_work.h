//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_SCORE_WORK_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_SCORE_WORK_H_

#include "brick_game_types.h"

/**
 * @addtogroup ScoreWork Работа с счетом
 * @{
 */

/**
 * Функция для обновления счета
 * @param game игра
 * @param score на сколько нужно увеличить счет
 */
void updateScore(GameInfo_t *game, int score);

/**
 * Функция считывания максимального счета из файла
 * @param game игра
 * @return максимальный счет
 */
int readHighScore(GameInfo_t *game, const char* filename);

/**
 * Функция записи максимального счета в файл
 * @param game игра
 * @param score максимальный счет
 */
int writeHighScore(GameInfo_t *game, int score, const char* filename);
/// @}

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_SCORE_WORK_H_
