//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_BRICK_GAME_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_BRICK_GAME_H_

#define GAME_CODE_SUCCESS 0
#define GAME_CODE_FILE_NOT_FOUND (-1)
#define GAME_CODE_ERROR_READ (-2)

#define GAME_FIELD_WIDTH 10
#define GAME_FIELD_HEIGHT 20

#define userInput(x) userInput##x
#define updateCurrentState(x) updateCurrentState##x
#define startNewGame(x) startNewGame##x
#define getMachineStatus(x) getMachineStatus##x


typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int **field;     // игровое поле
  int **next;      // следующая фигура
  int score;       // текущий счет
  int high_score;  // максимальный счет
  int level;       // текущий уровень
  int speed;       // текущая скорость
  int pause;       // Остановлена ли игра
} GameInfo_t;

typedef enum {
  Refresh,  // обновление игрового поля
  EndGame,  // конец игры
  Paused,   // пауза
  NewGame,  // новая игра(первое состояние автомата)
  SpawnFigure,  // появление новой фигуры
  SureEndGame   // подтверждение конца игры
} FiniteMachineStatus_t;
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_BRICK_GAME_H_
