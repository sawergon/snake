#include "../../include/common/score_work.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void updateScore(GameInfo_t *game, int score) {
  game->score += score;
  if (game->score > game->high_score) {
    game->high_score = game->score;
  }
}

int readHighScore(GameInfo_t *game, const char* filename) {
  int code = GAME_CODE_SUCCESS;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    code = GAME_CODE_FILE_NOT_FOUND;
  } else {
    if (fscanf(file, "%d", &game->high_score) != 1) {
      code = GAME_CODE_ERROR_READ;
      game->high_score = 0;
    }
    fclose(file);
  }
  return code;
}

int writeHighScore(GameInfo_t *game, int score, const char* filename) {
  /// открываем файл и считываем предыдущее значение
  int code = readHighScore(game, filename);
  if (code == GAME_CODE_FILE_NOT_FOUND) {
    /// если нет файла, то создаем его с рекордом 0
    game->high_score = 0;
  }
  FILE *file = fopen(filename, "w");
  code = GAME_CODE_SUCCESS;
  if (game->high_score < score) {
    fprintf(file, "%d", score);
    game->high_score = score;
  } else {
    fprintf(file, "%d", game->high_score);
  }
  fclose(file);
  return code;
}