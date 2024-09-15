//
// Created by alex on 11.09.24.
//

#include "../../include/snake/SnakeModel.h"
#include <stdexcept>
s21::SnakeModel::SnakeModel() = default;

s21::SnakeModel::~SnakeModel() {
  _field.~Field();
  _head.~Point();
  _tail.~Point();
}

void s21::SnakeModel::SetValueToField(int x, int y, Cell_t value) {
  _field.SetData(y, x, value);
}

void s21::SnakeModel::SetHead(int x, int y) {
  if (GAME_FIELD_WIDTH < x || GAME_FIELD_HEIGHT < y || x < 0 || y < 0) {
    throw std::out_of_range("Coordinate out of range");
  }
  _head.x = x;
  _head.y = y;
}

void s21::SnakeModel::SetTail(int x, int y) {
  if (GAME_FIELD_WIDTH < x || GAME_FIELD_HEIGHT < y || x < 0 || y < 0) {
    throw std::out_of_range("Coordinate out of range");
  }
  _tail.x = x;
  _tail.y = y;
}

void s21::SnakeModel::Move() {
  this->MoveHead();
  this->SetValueToField(_head.x, _head.y, Cell_t::Snake);
  this->SetValueToField(_tail.x, _tail.y, Cell_t::Empty);
  this->MoveTail();
}

void s21::SnakeModel::MoveHead() {
  if (this->CheckCollision()) {
    _head = _head + _move_direction;
  }
  _endGame = false;
}

void s21::SnakeModel::MoveTail() {
  if (_canMoveTail) {
    _tail = _tail + _move_direction;
  }
  _canMoveTail = true;
}

bool s21::SnakeModel::CheckCollision() {
  const Point tmp = _head + _move_direction;
  bool canMove = false;
  if (_field.GetData(tmp.y, tmp.x) == Cell_t::Apple) {
    UpdateScore();
    _canMoveTail = false;
    canMove = true;
  } else if (0 <= tmp.x && tmp.x < _field.GetWidth() && 0 <= tmp.y &&
             tmp.y < _field.GetHeight()) {
    canMove = true;
  }
  return canMove;
}

void s21::SnakeModel::DoAction(UserAction_t action,
                               [[maybe_unused]] bool hold) {
  if (action == Start && _status == NewGame) {
    StartGame();
  } else if (!_endGame) {
    switch (action) {
      case Pause:
        _pauseGame = !_pauseGame;
        _status = _pauseGame ? Paused : Refresh;
        break;
      case Terminate:
        if (_status != Paused) {
          _status = SureEndGame;
          _pauseGame = true;
        } else {
          _status = EndGame;
          FinishGame();
        }
        break;
      case Left:
        _status = Refresh;
        _move_direction.ChangeDirection(ToLeft);
        this->Move();
        break;
      case Right:
        _status = Refresh;
        _move_direction.ChangeDirection(ToRight);
        this->Move();
        break;
      case Up:
        _status = Refresh;
        _move_direction.ChangeDirection(ToUp);
        this->Move();
        break;
      case Down:
        _status = Refresh;
        _move_direction.ChangeDirection(ToDown);
        this->Move();
        break;
      default:
        _status = Refresh;
        this->Move();
    }
  }
}

void s21::SnakeModel::UpdateLevel() {
  if (const int tmp = _score / LEVEL_CHANGE_SCORE + 1;
    tmp > _level && tmp < MAX_LEVEL) {
    _level = tmp;
    _speed -= SPEED_INCREESEMENT;
  }
}

void s21::SnakeModel::UpdateScore() {
  _score++;
  if (_score > _high_score) {
    UpdateHighScore();
  }
  UpdateLevel();
}

void s21::SnakeModel::PlaceSnake() {
  const int start_x = _tail.x;
  const int start_y = _tail.y;
  for (int i = 0; i < START_SNAKE_LEN; i++) {
    _field.SetData(start_y + i, start_x, Snake);
  }
}

void s21::SnakeModel::PlaceApple() {
  bool isOkValue = false;
  while (!isOkValue) {
    const int x = static_cast<int>(random()) % GAME_FIELD_WIDTH;
    const int y = static_cast<int>(random()) % GAME_FIELD_HEIGHT;
    if (_field.GetData(y, x) == Empty) {
      isOkValue = true;
      _field.SetData(y, x, Apple);
    }
  }
}

void s21::SnakeModel::StartGame() {
  _endGame = false;
  _pauseGame = false;
  GameInfo_t game_info;
  int code = readHighScore(&game_info,
                           GAME_SNAKE_HIGH_SCORE_FILE);
  if (code == GAME_CODE_SUCCESS) {
    _high_score = game_info.high_score;
  }else {
    _high_score = 0;
  }
  _score = 0;
  _level = 1;
  _speed = START_SPEED;
  PlaceSnake();
  PlaceApple();
  _move_direction.ChangeDirection(ToDown);
}

void s21::SnakeModel::FinishGame() {
  _endGame = true;
  _pauseGame = true;
  GameInfo_t game_info;
  writeHighScore(&game_info, _score, GAME_SNAKE_HIGH_SCORE_FILE);
}

void s21::SnakeModel::MoveDirection::ChangeDirection(Direction_t direction) {
  switch (direction) {
    case ToUp:
      this->x = 0;
      this->y = -1;
      break;
    case ToDown:
      this->x = 0;
      this->y = 1;
      break;
    case ToLeft:
      this->x = -1;
      this->y = 0;
      break;
    case ToRight:
      this->x = 1;
      this->y = 0;
      break;
  }
}

s21::SnakeModel::Point& s21::SnakeModel::Point::operator+(
    const s21::SnakeModel::MoveDirection& move_direction) {
  this->x += move_direction.x;
  this->y += move_direction.y;
  return *this;
}