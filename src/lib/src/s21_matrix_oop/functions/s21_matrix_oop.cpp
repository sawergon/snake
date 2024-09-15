//
// Created by alex on 31.01.24.
//

#include "../s21_matrix_oop.h"

#include <iostream>
#include <stdexcept>

using namespace std;

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double*[rows_];
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]{};
    }
  } else {
    throw length_error("Matrix size can't be negative");
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; ++i) {
    this->matrix_[i] = new double[this->cols_];
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_ ||
      this->matrix_ == nullptr) {
    return false;
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      if (abs(this->matrix_[i][j] - other.matrix_[i][j]) > DIFFERENCE) {
        return false;
      }
    }
  }
  return true;
}
void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_ &&
      this->rows_ > 0) {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw length_error("For summing matrices should have same size");
  }
}
void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ == other.rows_ && this->cols_ == other.cols_ &&
      this->rows_ > 0) {
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else {
    throw length_error("For subbing matrices should have same size");
  }
}
void S21Matrix::MulNumber(const double num) {
  if (this->rows_ <= 0 || this->cols_ <= 0) {
    throw length_error("For mult matrices should have any size");
  }
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] *= num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.rows_) {
    throw length_error(
        "For mulling first matrix cols should eq to second matrix rows");
  }
  S21Matrix tmp(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      double new_cell_value = 0;
      for (int k = 0; k < other.rows_; ++k) {
        new_cell_value += other.matrix_[k][j] * this->matrix_[i][k];
      }
      tmp.setCell(i, j) = new_cell_value;
    }
  }
  this->resize(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      this->matrix_[i][j] = tmp(i, j);
    }
  }
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; ++i) {
    for (int j = 0; j < this->cols_; ++j) {
      result.setCell(j, i) = this->matrix_[i][j];
    }
  }
  return result;
}
double& S21Matrix::operator()(int i, int j) const {
  if (i >= this->rows_ || j >= this->cols_ || i < 0 || j < 0) {
    throw out_of_range("Index out of range");
  }

  return this->matrix_[i][j];
}
double& S21Matrix::setCell(int i, int j) const { return (*this)(i, j); }

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw length_error("Columns and rows should have same value");
  }
  if (this->rows_ <= 1) {
    throw length_error("Matrix size too small");
  }
  S21Matrix result(this->rows_, this->cols_);
  int minus_one_degree, matrix_size = this->rows_;
  for (int i = 0; i < matrix_size; ++i) {
    for (int j = 0; j < matrix_size; ++j) {
      minus_one_degree = (((i + j) & 1) == 0) ? 1 : -1;
      S21Matrix minor = this->CatMinor(i, j);
      double minor_determinant = minor.Determinant();
      result.setCell(i, j) = minus_one_degree * minor_determinant;
      minor.~S21Matrix();
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (this->rows_ != this->cols_) {
    throw length_error("Columns and rows should have same value");
  }
  return this->RecDeterminant();
}

double S21Matrix::RecDeterminant() {
  if (this->rows_ == 1) {
    return this->matrix_[0][0];
  }
  if (this->rows_ == 2) {
    return this->matrix_[0][0] * this->matrix_[1][1] -
           this->matrix_[0][1] * this->matrix_[1][0];
  }
  int minus_one_degree = 1;
  double result = 0;
  for (int i = 0; i < this->rows_; i++) {
    S21Matrix minor = this->CatMinor(i, 0);
    result =
        result + minus_one_degree * this->matrix_[i][0] * minor.Determinant();
    minus_one_degree = -minus_one_degree;
    minor.~S21Matrix();
  }
  return result;
}
S21Matrix S21Matrix::CatMinor(int i, int cols) {
  S21Matrix result(this->rows_ - 1, this->cols_ - 1);
  int di = 0;
  for (int ki = 0; ki < this->rows_ - 1; ki++) {
    if (ki == i) di = 1;
    int dj = 0;
    for (int kj = 0; kj < this->rows_ - 1; kj++) {
      if (kj == cols) dj = 1;
      result.setCell(ki, kj) = this->matrix_[ki + di][kj + dj];
    }
  }
  return result;
}
S21Matrix S21Matrix::InverseMatrix() {
  double det = this->Determinant();
  if (det == 0) {
    throw invalid_argument("Matrix is singular and cannot be inverted.");
  }
  S21Matrix inv = ((this->CalcComplements()).Transpose());
  inv.MulNumber(1 / det);
  return inv;
}
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}
S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    this->resize(other.rows_, other.cols_);
    for (int i = 0; i < this->rows_; ++i) {
      for (int j = 0; j < this->cols_; ++j) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}
bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}
bool S21Matrix::operator!=(const S21Matrix& other) {
  return !this->EqMatrix(other);
}
void S21Matrix::resize(int rows, int cols) {
  this->~S21Matrix();
  this->rows_ = rows;
  this->cols_ = cols;
  this->matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    this->matrix_[i] = new double[cols_]{};
  }
}
int S21Matrix::get_rows() const { return this->rows_; }
int S21Matrix::get_cols() const { return this->cols_; }
// void S21Matrix::PrintMatrix() {
//  for (int i = 0; i < this->rows_; ++i) {
//    for (int j = 0; j < this->cols_; ++j) {
//      cout << this->matrix_[i][j] << ' ';
//    }
//    cout << endl;
//  }
//}
double** S21Matrix::get_raw() const { return matrix_; }
