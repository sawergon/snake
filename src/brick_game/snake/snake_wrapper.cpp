#include "../../include/snake/SnakeModel.h"
#include "../../include/snake/snake.h"
#include <cstdio>

/**
 * Функция для обработки пользовательского ввода
 * @param action действие пользователя
 * @param hold зажатие клавиши
 */
void userInputSnake(UserAction_t action, bool hold) {
  s21::SnakeModel model = s21::getModel();
  model.DoAction(action, hold);
}

/**
 * Функция для обновления текущей игровой информации
 * @return текущая игровая информация
 */
GameInfo_t updateCurrentStateSnake() {
  s21::SnakeModel model = s21::getModel();
  GameInfo_t game;
  game.score = model.GetScore();
  game.level = model.GetLevel();
  game.high_score = model.GetHighScore();
  game.speed = model.GetSpeed();
  game.pause = model.GetPause();
  game.next = nullptr;
  game.field = model.get_raw();
  return game;
}

void startNewGameSnake() {
  s21::SnakeModel model = s21::getModel();
  FiniteMachineStatus_t *status = model.GetStatus();
  *status = NewGame;
}

FiniteMachineStatus_t* getMachineStatusSnake() {
  s21::SnakeModel model = s21::getModel();
  return model.GetStatus();
}
