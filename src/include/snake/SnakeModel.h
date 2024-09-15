//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_

#include "../common/brick_game_types.h"
#include "../common/score_work.h"
#include "Field.h"
#include "random"

#define GAME_SNAKE_HEAD_X 3
#define GAME_SNAKE_HEAD_Y 3
#define GAME_SNAKE_TAIL_X 3
#define GAME_SNAKE_TAIL_Y 0
#define START_SNAKE_LEN 4
#define LEVEL_CHANGE_SCORE 5
#define SPEED_INCREESEMENT 25
#define GAME_SNAKE_HIGH_SCORE_FILE "snake_high_score.txt"
#define START_SPEED 500

#define MAX_LEVEL 10

typedef enum { ToUp, ToDown, ToLeft, ToRight } Direction_t;

typedef enum { Empty, Snake, Apple } Cell_t;

namespace s21 {
class SnakeModel {
 private:
  class MoveDirection {
   public:
    int x = 0;
    int y = 1;
    MoveDirection() = default;
    void ChangeDirection(Direction_t direction);
  };

  class Point {
   public:
    int x;
    int y;

    Point() : x(0), y(0) {}

    Point(int x, int y) : x(x), y(y) {}

    Point& operator=(const Point& other) = default;
    Point& operator+(const MoveDirection& move_direction);
    ~Point() = default;
  };

  void MoveHead();
  void MoveTail();

  bool CheckCollision();
  void Move();
  void SetValueToField(int x, int y, Cell_t value);
  void SetHead(int x, int y);
  void SetTail(int x, int y);
  void UpdateLevel();
  void UpdateHighScore() { _high_score = _score; };
  void UpdateScore();
  void PlaceSnake();
  void PlaceApple();
  void StartGame();
  void FinishGame();

  Field _field = Field(GAME_FIELD_HEIGHT, GAME_FIELD_WIDTH);
  Point _head = Point(GAME_SNAKE_HEAD_X, GAME_SNAKE_HEAD_Y);
  Point _tail = Point(GAME_SNAKE_TAIL_X, GAME_SNAKE_TAIL_Y);
  MoveDirection _move_direction = MoveDirection();
  bool _canMoveTail = true;
  bool _endGame = true;
  bool _pauseGame = true;
  int _score = 0;
  int _high_score = 0;
  int _level = 1;
  int _speed = 500;
  FiniteMachineStatus_t _status = EndGame;

 public:
  /**
   * @brief Конструктор по умолчанию модели змейки
   *
   * Default constructor for SnakeModel class
   */
  SnakeModel();
  /**
   * @brief Деструктор модели змейки
   *
   * Destructor for SnakeModel class
   */
  ~SnakeModel();
  /**
   * @brief Получение игрового поля
   * @return копия игрового поля
   */
  Field GetField() { return {_field}; }
  /**
   * @brief Обработка пользовательского ввода
   * @param action действие пользователя
   * @param hold зажатие клавиши
   */
  void DoAction(UserAction_t action, bool hold);
  /**
   * @brief Получение состояния игры
   * @return true если игра закончена, false если игра продолжается
   */
  [[nodiscard]] bool IsEndGame() const { return _endGame; }
  /**
   * @brief Получение состояния паузы
   * @return true если игра на паузе, false если игра не на паузе
   */
  [[nodiscard]] bool IsPaused() const { return _pauseGame; }
  /**
   * @brief Получение текущего счета
   * @return текущий счет
   */
  [[nodiscard]] int GetScore() const { return _score; }
  /**
   * @brief Получение текущего уровня
   * @return текущий уровень
   */
  [[nodiscard]] int GetLevel() const { return _level; }
  /**
   * @brief Получение максимального счета
   * @return максимальный счет
   */
  [[nodiscard]] int GetHighScore() const { return _high_score; }
  /**
   * @brief Получение текущей скорости змейки
   * @return текущая скорость змейки (мс)
   */
  [[nodiscard]] int GetSpeed() const { return 1000 / _level; }
  /**
   * @brief Получение состояния паузы
   * @return true если игра на паузе, false если игра не на паузе
   */
  [[nodiscard]] bool GetPause() const { return _pauseGame; }
  int **get_raw() { return reinterpret_cast<int**>(_field.get_raw()); }
  FiniteMachineStatus_t *GetStatus() {return &_status;}
};

    inline SnakeModel getModel()
    {
        static SnakeModel model = SnakeModel();
        return model;
    }
} // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKEMODEL_H_
