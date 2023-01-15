#include "s21_matrix.h"

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
  int error = NO_ERROR;
  if (columns < 1 || rows < 1)
    error = ERROR_INVALID_MATRIX;
  else {
    result->columns = columns;
    result->rows = rows;
    result->matrix = calloc(rows, sizeof(double *));

    if (result->matrix == NULL)
      error = ERROR_INVALID_MATRIX;
    else {
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          error = ERROR_INVALID_MATRIX;
          break;
        }
      }
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *const A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i]) free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A->columns) {
    A->columns = 0;
  }
  if (A->rows) {
    A->rows = 0;
  }
}

int s21_check_matrix(matrix_t *A) {
  int answer = A->matrix != NULL && A->columns > 0 && A->rows > 0;
  return answer;
}