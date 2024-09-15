#ifndef C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
#define C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../common/brick_game_types.h"
#include "../common/score_work.h"
#include "game_init.h"
#include "matrix_work.h"

#define AMOUNT_OF_FIGURES 7
#define ROTATE_DIRECTIONS 4
#define FIGURE_COORD_SIZE 4

// глобальные координаты
#define FIGURE_START_POSITION_X 3
#define FIGURE_START_POSITION_Y 0

typedef enum {
  I,  // прямая линия
  O,  // квадрат
  T,  // т образная
  J,  // Г
  L,  // обратная Г
  S,  // зигзаг
  Z   // обратный зигзаг
} FigureType_t;

typedef enum { ToUp, ToDown, ToLeft, ToRight } RotateDirection_t;

typedef struct {
  int data[FIGURE_COORD_SIZE][FIGURE_COORD_SIZE];
} Figure_t;
// по типу фигуры и направлению поворота можно получить текущую фигуру из
// массива фигур
typedef struct {
  int x;  // самый левый пиксель поля фигуры в координатах игрового поля
  int y;  // самый верхний пиксель поля фигуры в координатах игрового поля
  FigureType_t type;       // тип фигуры
  FigureType_t next_type;  // следующий тип фигуры
  int **clean_field;  // игровое поле без этой самой фигуры
  RotateDirection_t rotate;  // направление поворота
  Figure_t positionArr[AMOUNT_OF_FIGURES][ROTATE_DIRECTIONS];
} FigureInfo_t;

typedef struct {
  int data[4][2];
} Hint_t;

/**
 * @addtogroup GameWork Работа игры
 * @{
 */

/**
 * Функция для обработки пользовательского ввода
 * @param action действие пользователя
 * @param hold зажатие клавиши
 */
void userInputTetris(UserAction_t action, __attribute__((unused)) bool hold);

/**
 * Функция для обновления текущей игровой информации
 * @return текущая игровая информация
 */
GameInfo_t updateCurrentStateTetris();

/**
 * Функция для получения состояния автомата
 * @return состояние автомата
 */
FiniteMachineStatus_t *getMachineStatusTetris();

/**
 * Функция для начала новой игры
 */
void startNewGameTetris();

/**
 * Функция для получения подсказки
 * @return подсказка
 */
Hint_t getHint();
/// @}

/**
 * @addtogroup FigureWork Работа с фигурами
 * @{
 */

/**
 * Функция для получения информации о фигуре
 * @return информация о фигуре
 */
FigureInfo_t *getFigureInfo();

/**
 * Функция для заполнения информации о всех фигурах (нужно для инициализации)
 * @param figure информация о фигуре
 */
void fillPosArr(FigureInfo_t *figure);

/**
 * Функция для размещения фигуры на поле
 * @param figure информация о фигуре
 * @param game игра
 */
void placeFigure(FigureInfo_t *figure, GameInfo_t *game);

/**
 * Функция для получения текущей фигуры
 * @return матрица 4х4 текущей фигуры
 */
Figure_t getCurrentFigure();

/**
 * Функция для получения фигуры после вращения
 * @return матрица 4х4 следующей фигуры
 */
Figure_t getNextFigureRotate();

/**
 * Функция для осуществления вращения фигуры
 * @param figure_info информация о фигуре
 */
void doRotate(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры влево
 * @param figure_info информация о фигуре
 */
void moveLeft(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры вправо
 * @param figure_info информация о фигуре
 */
void moveRight(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры вниз на один шаг
 * @param figure_info информация о фигуре
 */
void moveDown(FigureInfo_t *figure_info);

/**
 * Функция для перемещения фигуры в самый низ
 * @param figure_info
 */
void dropDown(FigureInfo_t *figure_info);

/**
 * Получение случайного типа фигуры
 * @return
 */
FigureType_t getRandomFigureType();

/**
 * Функция для проверки возможности перемещения фигуры вниз
 * @param figure_info информация о фигуре
 * @return возможно ли смещение
 */
bool canMovingDown(FigureInfo_t *figure_info);

/**
 * Функция для вычисления счета
 * @param level Текущий уровень
 * @param lines_dropped Количество собранных линий
 * @return Общий счет
 */
int calculateScore(int lines_dropped);
/// @}
#endif  // C7_BRICKGAME_V1_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H_
