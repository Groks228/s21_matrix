#include <float.h>

#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int answer = SUCCESS;
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    answer = FAILURE;
  } else if (!s21_check_size(A, B)) {
    answer = FAILURE;
  }
  if (answer != FAILURE) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-6) {
          answer = FAILURE;
          break;
        }
      }
    }
  }

  return answer;
}

int s21_check_size(matrix_t *A, matrix_t *B) {
  int check = 1;

  if ((A->rows != B->rows) || (A->columns != B->columns)) check = 0;

  return check;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    error = ERROR_INVALID_MATRIX;
  } else if (!s21_check_size(A, B)) {
    error = ERROR_CALCULATIONS;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((A->matrix[i][j] + B->matrix[i][j]) > DBL_MAX ||
            (A->matrix[i][j] + B->matrix[i][j]) < -DBL_MAX)
          error = ERROR_CALCULATIONS;
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    error = ERROR_INVALID_MATRIX;
  } else if (!s21_check_size(A, B)) {
    error = ERROR_CALCULATIONS;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((A->matrix[i][j] - B->matrix[i][j]) > DBL_MAX ||
            (A->matrix[i][j] - B->matrix[i][j]) < -DBL_MAX)
          error = ERROR_CALCULATIONS;
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return error;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A)) {
    error = ERROR_INVALID_MATRIX;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if ((A->matrix[i][j] * number) > DBL_MAX ||
            (A->matrix[i][j] * number) < -DBL_MAX)
          error = ERROR_CALCULATIONS;
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A) || !s21_check_matrix(B)) {
    error = ERROR_INVALID_MATRIX;
  } else if ((A->columns != B->rows) || (A->rows != B->columns)) {
    error = ERROR_CALCULATIONS;
  } else {
    error = s21_create_matrix(A->rows, B->columns, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          if ((A->matrix[i][k] * B->matrix[k][j]) > DBL_MAX ||
              (A->matrix[i][k] * B->matrix[k][j]) < -DBL_MAX)
            error = ERROR_CALCULATIONS;

          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return error;
}
