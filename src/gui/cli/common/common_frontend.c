#include "../../../include/common/common_frontend.h"
#include "../../../include/common/brick_game_types.h"

#define GAME_LIST_START 3

void displayStartMessage(char** games_list, int amount) {
  clear();
  mvprintw(0, 5, "This is brick game");
  mvprintw(1, 7, "by kimikodo");
  mvprintw(2, 0, "You can choose one of the games");
  for (int i = 0; i < amount; i++) {
    mvprintw(GAME_LIST_START + i, 1, games_list[i]);
  }
  mvprintw(GAME_LIST_START + amount, 1, "Exit Brick Game");
}

int chooseGame(int amount) {
  UserAction_t action = Left;
  int choosen_game = -1;
  int current_game = 0;
  attron(A_BLINK);
  mvprintw(GAME_LIST_START, 0, ">");
  while (action != Terminate && choosen_game == -1) {
    action = getAction();
    if (action == Start) {
      choosen_game = current_game;
    } else if (action == Up) {
      mvprintw(current_game + GAME_LIST_START, 0, " ");
      current_game = (current_game - 1 + amount) % amount;
      mvprintw(current_game + GAME_LIST_START, 0, ">");
    } else if (action == Down) {
      mvprintw(current_game + GAME_LIST_START, 0, " ");
      current_game = (current_game + 1) % amount;
      mvprintw(current_game + GAME_LIST_START, 0, ">");
    }
  }
  attroff(A_BLINK);
  return choosen_game;
}

void displayStartMessageGame(char *game_name) {
    clear();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    mvprintw(0, 0, game_name);
    attroff(COLOR_PAIR(2));
    mvprintw(0, 8, "by kimikodo");
    mvprintw(1, 0, "Have nice game");
    attron(COLOR_PAIR(1));
    mvprintw(3, 0, "Use arrows to move");
    mvprintw(4, 0, "P to pause");
    mvprintw(5, 0, "SPACE  to rotate");
    mvprintw(6, 0, "Q to quite");
    attroff(COLOR_PAIR(1));

    attron(A_BLINK | COLOR_PAIR(2));
    mvprintw(8, 0, "Press ENTER to start");
    attroff(A_BLINK | COLOR_PAIR(2));
    refresh();
}

void displayEndMessageGame(int score, char *game_name) {
    clear();
    mvprintw(0, 0, "Thank you for playing");
    mvprintw(0, 21, game_name);
    mvprintw(1, 0, "PRESS Q TO EXIT");
    mvprintw(2, 0, "PRESS ENTER TO RESTART");
    mvprintw(3, 0, "YOUR SCORE: %d", score);
    refresh();
}

void displayErrorMessage() {
    clear();
    mvprintw(0, 0, "Error");
    refresh();
}

void displayHoldMessage() {
    printRectangle(4, 8, 4, 24);
    attron(A_BLINK);
    mvprintw(5, 5, "Game on hold       ");
    attroff(A_BLINK);
    mvprintw(6, 5, "Press P to continue");
    mvprintw(7, 5, "Press Q to exit    ");
    refresh();
}

void displaySureEndGameMessage() {
    attron(A_BLINK);
    printRectangle(4, 8, 4, 29);
    attroff(A_BLINK);
    mvprintw(5, 5, "Sure want end game?    ");
    mvprintw(6, 5, "Press Q to exit        ");
    mvprintw(7, 5, "Press ENTER to continue");
    refresh();
}

bool getStartCommand() {
    bool run = false;
    bool terminate = false;
    while (!run && !terminate) {
        UserAction_t action = getAction();
        if (action == Start) {
            run = true;
        } else if (action == Terminate) {
            terminate = true;
        }
    }
    return run;
}

void printRectangle(int top_y, int bottom_y, int left_x, int right_x) {
    mvaddch(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;
    for (; i < right_x; i++) {
        mvaddch(top_y, i, ACS_HLINE);
    }
    mvaddch(top_y, i, ACS_URCORNER);

    i = top_y + 1;
    for (; i < bottom_y; i++) {
        mvaddch(i, left_x, ACS_VLINE);
        mvaddch(i, right_x, ACS_VLINE);
    }
    mvaddch(bottom_y, left_x, ACS_LLCORNER);

    i = left_x + 1;
    for (; i < right_x; i++) {
        mvaddch(bottom_y, i, ACS_HLINE);
    }
    mvaddch(bottom_y, i, ACS_LRCORNER);
}

UserAction_t getAction() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            return Left;
        case KEY_RIGHT:
            return Right;
        case KEY_UP:
            return Up;
        case KEY_DOWN:
            return Down;
        case KEY_ACTION:
            return Action;
        case KEY_QUIT:
            return Terminate;
        case KEY_START:
            return Start;
        case 'p':
            return Pause;
        default:
            return -1;
    }
}
