#include "../../include/tetris/game_init.h"

#include <stdbool.h>
#include <stdlib.h>
GameInfo_t *createGame() {
  GameInfo_t *game = getGameState();
  game->field = NULL;
  game->next = NULL;
  game->score = 0;
  game->high_score = 0;
  game->level = 0;
  game->speed = 0;
  game->pause = 0;
  return game;
}

void initGame(GameInfo_t *game, const char* filename) {
  game->field = createMatrix(GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH);
  game->next = NULL;
  game->score = 0;
  game->level = 1;
  game->speed = 500;
  game->pause = false;
  if (readHighScore(game, filename) == GAME_CODE_FILE_NOT_FOUND) {
    writeHighScore(game, 0, GAME_TETRIS_HIGH_SCORE_FILE);
  }
}

GameInfo_t *getGameState() {
  static GameInfo_t game;
  return &game;
}