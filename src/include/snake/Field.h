//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_SNAKE_FIELD_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_SNAKE_FIELD_H_

#include "../../lib/src/s21_matrix_oop/s21_matrix_oop.h"

namespace s21 {
class Field {
 private:
  S21Matrix _cells;
  int _height;
  int _width;

 public:
  Field(int height, int width)
      : _cells(height, width), _height(height), _width(width){};
  ~Field() {
    _cells.~S21Matrix();
    _height = 0;
    _width = 0;
  };
  Field(const Field &other) {
    _height = other._height;
    _width = other._width;
    _cells = S21Matrix(_height, _width);
    for (int i = 0; i < _height; i++) {
      for (int j = 0; j < _width; j++) {
        _cells(i, j) = other._cells(i, j);
      }
    }
  }
  int GetData(int y, int x) { return (int)_cells(y, x); };
  [[nodiscard]] int GetHeight() const { return _height; };
  [[nodiscard]] int GetWidth() const { return _width; };
  void SetData(int y, int x, int value) { _cells(y, x) = value; };
  void Clear() {
    for (int i = 0; i < _height; i++) {
      for (int j = 0; j < _width; j++) {
        _cells(i, j) = 0;
      }
    }
  }
  double ** get_raw() { return _cells.get_raw(); }
};
}  // namespace s21
#endif  // CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_SNAKE_FIELD_H_
