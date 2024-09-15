//
// Created by alex on 11.09.24.
//

#ifndef CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_MATRIX_WORK_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_MATRIX_WORK_H_

/**
 * @addtogroup MatrixWork Работа с матрицами поля
 * @{
 */
/**
 * Функция для создания матрицы
 * @param height высота матрицы
 * @param width ширина матрицы
 * @return созданная матрица
 */
int **createMatrix(int height, int width);

/**
 * Функция для вывода матрицы на экран
 * @param game игра
 */
void printMatrix(int **matrix, int height, int width);

/**
 * Функция для освобождения матрицы
 * @param matrix матрица
 * @param height высота матрицы
 * @param width ширина матрицы
 */
void destroyMatrix(int ***matrix, int height);

/**
 * Функция для копирования матрицы
 * @param matrix матрица для копирования
 * @param height высота
 * @param width ширина
 * @return скопированная матрица
 */
int **copyMatrix(int **matrix, int height, int width);

/**
 * Функция для перемещения матриц
 * @param src Матрица для перемещения
 * @param dst Матрица куда
 * @param height
 * @param width
 */
void moveMatrix(int **src, int **dst, int height, int width);
/// @}

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_INCLUDE_COMMON_MATRIX_WORK_H_
