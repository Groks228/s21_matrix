#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A)) {
    error = ERROR_INVALID_MATRIX;
  } else {
    error = s21_create_matrix(A->columns, A->rows, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = NO_ERROR;
  if (!s21_check_matrix(A)) {
    error = ERROR_INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = ERROR_CALCULATIONS;
  } else {
    error = s21_create_matrix(A->rows, A->columns, result);
  }

  if (error == NO_ERROR) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double minor_value = 0;
        matrix_t minor = {0};
        s21_minor(i + 1, j + 1, A, &minor);
        s21_determinant(&minor, &minor_value);
        result->matrix[i][j] = minor_value * pow(-1, (i + j));
        s21_remove_matrix(&minor);
      }
    }
  }

  return error;
}

int s21_minor(int row, int column, matrix_t *A, matrix_t *result) {
  int error = NO_ERROR;
  error = s21_create_matrix(A->rows - 1, A->columns - 1, result);

  if (error == NO_ERROR) {
    row--;
    column--;
    int i_minor = 0;
    for (int i = 0; i < A->rows; i++) {
      int j_minor = 0;
      for (int j = 0; j < A->columns; j++) {
        if (i != row && j != column) {
          result->matrix[i_minor][j_minor] = A->matrix[i][j];
          j_minor++;
        }
      }
      if (i != row) i_minor++;
    }
  }

  return error;
}

double s21_minor_calc(matrix_t A) {
  double res = 0;
  res = A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0];

  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = NO_ERROR;
  *result = 0;
  if (!s21_check_matrix(A)) {
    error = ERROR_INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = ERROR_CALCULATIONS;
  }
  if (error == NO_ERROR) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else {
      double temp = 0;
      int sign = 1;
      for (int j = 0; j < A->rows; j++) {
        matrix_t minor = {0};
        error = s21_minor(1, j + 1, A, &minor);
        if (error == NO_ERROR) {
          if (minor.rows == 2)
            temp = s21_minor_calc(minor);
          else
            s21_determinant(&minor, &temp);
          s21_remove_matrix(&minor);
          *result += A->matrix[0][j] * temp * sign;
          sign *= -1;
        }
      }
    }
  }

  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = NO_ERROR;
  double determinant_result = 0;

  if (!s21_check_matrix(A)) {
    error = ERROR_INVALID_MATRIX;
  } else if (A->rows != A->columns) {
    error = ERROR_CALCULATIONS;
  } else {
    s21_determinant(A, &determinant_result);
    if (fabs(determinant_result - 0) < 1e-6) error = ERROR_CALCULATIONS;
  }

  if (error == NO_ERROR) {
    matrix_t temp_matrix = {0};
    s21_calc_complements(A, &temp_matrix);
    s21_transpose(&temp_matrix, result);
    s21_remove_matrix(&temp_matrix);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = result->matrix[i][j] / determinant_result;
      }
    }
  }

  return error;
}