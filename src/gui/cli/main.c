#include "../../include/tetris/tetris_cli.h"
#include "../../include/snake/snake_cli.h"
#include "../../include/common/common_frontend.h"

#define AMOUNT_OF_GAMES 2

typedef void (*loopFnc)();

int main() {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  //    wresize(stdscr, WIN_HEIGHT, WIN_WIDTH);
  keypad(stdscr, TRUE);

  loopFnc games[AMOUNT_OF_GAMES] = {tetrisGameLoop, snakeGameLoop};
  char *games_names[AMOUNT_OF_GAMES] = {GAME_TETRIS_NAME, GAME_SNAKE_NAME};
  bool run = true;
  while (run) {
    displayStartMessage(games_names, AMOUNT_OF_GAMES);
    int game_id = chooseGame(AMOUNT_OF_GAMES + 1);
    if (game_id == AMOUNT_OF_GAMES) {
      run = false;
    }else if (game_id >= 0) {
      loopFnc gameLoop = games[game_id];
      gameLoop();
    }
  }

  endwin();

  //  printf("Hello");
  //  tetrisGameLoop();
  return 0;
}
