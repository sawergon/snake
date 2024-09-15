#include "../../../include/snake/snake_cli.h"
#include "../../../include/snake/snake.h"
#include "../../../include/common/common_frontend.h"
#include "ncurses.h"

void displayGameSnake(GameInfo_t *game) {
  clear();
  printRectangle(0, GAME_FIELD_HEIGHT+1, 0, GAME_FIELD_WIDTH+1);
  printRectangle(0, GAME_FIELD_HEIGHT+1, GAME_FIELD_WIDTH+2, GAME_FIELD_WIDTH + 21);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  for (int y = 0; y < GAME_FIELD_HEIGHT; y++) {
    for (int x = 0; x < GAME_FIELD_WIDTH; x++) {
      if (game->field[y][x] == 0) {
        mvaddch(y + 1, x + 1, ' ');
      } else if (game->field[y][x] == 1) {
        attron(COLOR_PAIR(2));
        mvaddch(y + 1, x + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(2));
      } else {
        attron(COLOR_PAIR(1));
        mvaddch(y + 1, x + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(1));
      }
    }
  }
  refresh();
}

void displayHelpInfoSnake(GameInfo_t *game) {
  int delta_y = 9;
  int delta_x = 12;
  mvprintw(delta_y++, delta_x, "SCORE: %d", game->score);
  mvprintw(delta_y++, delta_x, "HIGHSCORE: %d", game->high_score);
  mvprintw(delta_y++, delta_x, "LEVEL: %d", game->level);
  mvprintw(delta_y, delta_x, "SPEED: %d", game->speed);
}

void snakeGameLoop() {
  bool hold = false; // зажата ли клавиша
  bool run = false;

  displayStartMessageGame(GAME_SNAKE_NAME);

  run = getStartCommand();
  if (run) {
    startNewGame(Snake)();
    userInput(Snake)(Start, false);
  }
  while (run) {
    GameInfo_t game = updateCurrentState(Snake)();
    timeout(game.speed);
    const FiniteMachineStatus_t *status = getMachineStatus(Snake)();
    if (*status == SureEndGame) {
      displaySureEndGameMessage();
      run = getStartCommand();
      if (run) {
        userInput(Snake)(Pause, false);
      } else {
        userInput(Snake)(Terminate, false);
      }
    }
    if (*status == EndGame) {
      displayEndMessageGame(game.score, GAME_SNAKE_NAME);
      run = getStartCommand();
      if (run) {
        startNewGame(Snake)();
        userInput(Snake)(Start, false);
      }
    } else if (*status == Paused) {
      displayHoldMessage();
    } else if (*status == Refresh) {
      displayGameSnake(&game);
      displayHelpInfoSnake(&game);
    }
    userInput(Snake)(getAction(), hold);
  }
}