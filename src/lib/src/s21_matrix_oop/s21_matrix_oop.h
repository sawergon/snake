//
// Created by alex on 31.01.24.
//

#ifndef CPP1_S21_MATRIXPLUS_1_SRC_FUNCTIONS_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_1_SRC_FUNCTIONS_S21_MATRIX_OOP_H_

#define DIFFERENCE 1e-7

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Строки и столбцы
  double** matrix_;  // Указатель на область памяти, где расположена матрица
  double RecDeterminant();
  S21Matrix CatMinor(int i, int cols);

 public:
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Конструктор с параметрами
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other) noexcept;  // Конструктор переноса
  ~S21Matrix();                           // Деструктор

  bool EqMatrix(const S21Matrix& other);  // Сравнение матриц
  void SumMatrix(const S21Matrix& other);  // Прибавление матрицы к текущей
  void SubMatrix(const S21Matrix& other);  // Вычитание матрицы из текущей
  void MulNumber(const double num);  // Умножение матрицы на число
  void MulMatrix(const S21Matrix& other);  // умножении матрицы на матрицу
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*=(const double num);
  S21Matrix operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  bool operator!=(const S21Matrix& other);
  double& operator()(int i, int j) const;
  double& setCell(int i, int j) const;
  void resize(int rows, int cols);

  int get_rows() const;
  int get_cols() const;
  double** get_raw() const;

  void PrintMatrix();
};

#endif  // CPP1_S21_MATRIXPLUS_1_SRC_FUNCTIONS_S21_MATRIX_OOP_H_
