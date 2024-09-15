#include <stdbool.h>
#include "../../../include/common/common_frontend.h"
#include "../../../include/tetris/tetris_cli.h"
#include "../../../include/tetris/tetris.h"

void displayGameTetris(GameInfo_t *game) {
  clear();
  printRectangle(0, GAME_FIELD_HEIGHT+1, 0, GAME_FIELD_WIDTH+1);
  printRectangle(0, GAME_FIELD_HEIGHT+1, GAME_FIELD_WIDTH+2, GAME_FIELD_WIDTH + 21);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  for (int y = 0; y < GAME_FIELD_HEIGHT; y++) {
    for (int x = 0; x < GAME_FIELD_WIDTH; x++) {
      if (game->field[y][x] == 0) {
        mvaddch(y + 1, x + 1, ' ');
      } else {
        attron(COLOR_PAIR(game->field[y][x]));
        mvaddch(y + 1, x + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(game->field[y][x]));
      }
    }
  }
  Hint_t hint = getHint();
  if (hint.data[0][0] != 0) {
    for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
      if (game->field[hint.data[i][0]][hint.data[i][1]] == 0) {
        attron(COLOR_PAIR(1));
        mvaddch(hint.data[i][0] + 1, hint.data[i][1] + 1, ACS_BLOCK);
        attroff(COLOR_PAIR(1));
      }
    }
  }
  refresh();
}

void displayHelpInfoTetris(GameInfo_t *game) {
  int delta_y = 1;
  int delta_x = 13;
  mvprintw(delta_y, delta_x, "NEXT FIGURE");
  delta_y += 1;
  printRectangle(delta_y, delta_y + 5, delta_x, delta_x + 5);
  delta_y += 1;
  delta_x += 1;
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  for (int i = 0; i < FIGURE_COORD_SIZE; i++) {
    for (int j = 0; j < FIGURE_COORD_SIZE; ++j) {
      if (game->next[i][j] != 0) {
        attron(COLOR_PAIR(game->next[i][j]));
        mvaddch(delta_y + i, delta_x + j, ACS_CKBOARD);
        attroff(COLOR_PAIR(game->next[i][j]));
      }
    }
  }
  delta_y += 5;
  delta_x -= 1;
  mvprintw(delta_y++, delta_x, "SCORE: %d", game->score);
  mvprintw(delta_y++, delta_x, "HIGHSCORE: %d", game->high_score);
  mvprintw(delta_y++, delta_x, "LEVEL: %d", game->level);
  mvprintw(delta_y, delta_x, "SPEED: %d", game->speed);
}

void tetrisGameLoop() {
  bool hold = false; // зажата ли клавиша
  bool run = false;

  displayStartMessageGame(GAME_TETRIS_NAME);

  run = getStartCommand();
  if (run) {
    startNewGame(Tetris)();
    userInput(Tetris)(Start, false);
  }
  while (run) {
    GameInfo_t game = updateCurrentState(Tetris)();
    timeout(game.speed);
    const FiniteMachineStatus_t *status = getMachineStatus(Tetris)();
    if (*status == SureEndGame) {
      displaySureEndGameMessage();
      run = getStartCommand();
      if (run) {
        userInput(Tetris)(Pause, false);
      } else {
        userInput(Tetris)(Terminate, false);
      }
    }
    if (*status == EndGame) {
      displayEndMessageGame(game.score, GAME_TETRIS_NAME);
      run = getStartCommand();
      if (run) {
        startNewGame(Tetris)();
        userInput(Tetris)(Start, false);
      }
    } else if (*status == Paused) {
      displayHoldMessage();
    } else if (*status == Refresh) {
      displayGameTetris(&game);
      displayHelpInfoTetris(&game);
    }
    userInput(Tetris)(getAction(), hold);
  }
}