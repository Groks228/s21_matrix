#include "suitecases.h"

void print_matrix(matrix_t m) {
  for (int i = 0; i < m.rows; i++) {
    for (int j = 0; j < m.columns; j++) {
      printf("%6lf ", m.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

// equal matrix 1, 1
START_TEST(equal_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = i;
    }
  }
  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

// non_equal matrix 5, 5
START_TEST(equal_test_2) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = j;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

// non_existent matrix 5, 5
START_TEST(equal_test_3) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(rows, columns, &m1);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = j;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), 0);
  s21_remove_matrix(&m1);
}
END_TEST

// create valid matrix
START_TEST(create_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t m1 = {0};

  ck_assert_int_eq(s21_create_matrix(rows, columns, &m1), 0);
  s21_remove_matrix(&m1);
}
END_TEST

// create invalid matrix
START_TEST(create_test_2) {
  int rows = 1;
  int columns = 0;
  matrix_t m1 = {0};

  ck_assert_int_eq(s21_create_matrix(rows, columns, &m1), 1);
  s21_remove_matrix(&m1);
}
END_TEST

// create valid matrix 1000, 1000
START_TEST(create_test_3) {
  int rows = 1000;
  int columns = 1000;
  matrix_t m1 = {0};

  ck_assert_int_eq(s21_create_matrix(rows, columns, &m1), 0);
  s21_remove_matrix(&m1);
}
END_TEST

// normal matrix
START_TEST(sum_test_1) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = i;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// invalid matrix
START_TEST(sum_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);

  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in calculations
START_TEST(sum_test_3) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = DBL_MAX;
      m2.matrix[i][j] = DBL_MAX;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in size
START_TEST(sum_test_4) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 4, &m1);
  s21_create_matrix(4, 1, &m2);
  s21_create_matrix(4, 4, &res);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = i;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// normal matrix
START_TEST(sub_test_1) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = i;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// invalid matrix
START_TEST(sub_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);

  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in calculations
START_TEST(sub_test_3) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = DBL_MAX;
      m2.matrix[i][j] = -DBL_MAX;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in size
START_TEST(sub_test_4) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 4, &m1);
  s21_create_matrix(4, 1, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = i;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// normal matrix
START_TEST(mult_matrix_test_1) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(3, 5, &m1);
  s21_create_matrix(5, 3, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m2.rows; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[j][i] = i;
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// invalid matrix
START_TEST(mult_matrix_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in calculations
START_TEST(mult_matrix_test_3) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  s21_create_matrix(rows, columns, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = DBL_MAX;
      m2.matrix[i][j] = DBL_MAX;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// error in size
START_TEST(mult_matrix_test_4) {
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 4, &m1);
  s21_create_matrix(3, 2, &m2);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i;
    }
  }
  for (int i = 0; i < m2.rows; i++) {
    for (int j = 0; j < m2.columns; j++) {
      m2.matrix[i][j] = i;
    }
  }

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
}
END_TEST

// normal matrix
START_TEST(mult_number_test_1) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  double num = 15.0;
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i;
    }
  }
  ck_assert_int_eq(s21_mult_number(&m1, num, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// invalid matrix
START_TEST(mult_number_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  double num = 15.0;
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);

  ck_assert_int_eq(s21_mult_number(&m1, num, &res), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// error in calculations
START_TEST(mult_number_test_3) {
  int rows = 5;
  int columns = 5;
  matrix_t m1 = {0};
  double num = 15.0;
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = DBL_MAX;
    }
  }

  ck_assert_int_eq(s21_mult_number(&m1, num, &res), 2);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// normal transpose
START_TEST(transpose_test_1) {
  matrix_t m1 = {0};
  matrix_t res = {0};
  s21_create_matrix(3, 5, &m1);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = i;
    }
  }

  ck_assert_int_eq(s21_transpose(&m1, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// invalid matrix
START_TEST(transpose_test_2) {
  int rows = 0;
  int columns = 5;
  matrix_t m1 = {0};
  matrix_t res = {0};
  s21_create_matrix(rows, columns, &m1);

  ck_assert_int_eq(s21_transpose(&m1, &res), 1);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// borderline case
START_TEST(transpose_test_3) {
  matrix_t m1 = {0};
  matrix_t res = {0};
  s21_create_matrix(1, 1, &m1);
  for (int i = 0; i < m1.rows; i++) {
    for (int j = 0; j < m1.columns; j++) {
      m1.matrix[i][j] = 5;
    }
  }

  ck_assert_int_eq(s21_transpose(&m1, &res), 0);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&res);
}
END_TEST

// matrix 3,3
START_TEST(determinant_test_1) {
  matrix_t m1;
  s21_create_matrix(3, 3, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[1][0] = 4;
  m1.matrix[1][1] = 5;
  m1.matrix[1][2] = 6;
  m1.matrix[2][0] = 7;
  m1.matrix[2][1] = 8;
  m1.matrix[2][2] = 8;
  double result = 0;

  ck_assert_int_eq(s21_determinant(&m1, &result), 0);
  ck_assert_double_eq(result, 3.0);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t m1;
  s21_create_matrix(4, 4, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[0][2] = 3;
  m1.matrix[0][3] = 3;
  m1.matrix[1][0] = 2;
  m1.matrix[1][1] = 5;
  m1.matrix[1][2] = 1;
  m1.matrix[1][3] = 1;
  m1.matrix[2][0] = 2;
  m1.matrix[2][1] = -2;
  m1.matrix[2][2] = 0;
  m1.matrix[2][3] = 0;
  m1.matrix[3][0] = 4;
  m1.matrix[3][1] = -2;
  m1.matrix[3][2] = 1;
  m1.matrix[3][3] = 2;
  double result = 0;

  ck_assert_int_eq(s21_determinant(&m1, &result), 0);
  ck_assert_double_eq(result, -36.0);
  s21_remove_matrix(&m1);
}
END_TEST

// matrix 2,2
START_TEST(determinant_test_3) {
  matrix_t m1;
  s21_create_matrix(2, 2, &m1);
  m1.matrix[0][0] = 1;
  m1.matrix[0][1] = 2;
  m1.matrix[1][0] = 2;
  m1.matrix[1][1] = 5;

  double result = 0;

  ck_assert_int_eq(s21_determinant(&m1, &result), 0);
  ck_assert_double_eq(result, 1);
  s21_remove_matrix(&m1);
}
END_TEST

// matrix 1,1
START_TEST(determinant_test_4) {
  matrix_t m1;
  s21_create_matrix(1, 1, &m1);
  m1.matrix[0][0] = 4;

  double result = 0;

  ck_assert_int_eq(s21_determinant(&m1, &result), 0);
  ck_assert_double_eq(result, 4);
  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(determinant_test_5) {
  matrix_t m1;
  s21_create_matrix(1, 3, &m1);

  double result = 0;

  ck_assert_int_eq(s21_determinant(&m1, &result), 2);
  ck_assert_double_eq(result, 0);
  s21_remove_matrix(&m1);
}
END_TEST

// matrix 3,3
START_TEST(complements_test_1) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;
  matrix.matrix[1][2] = 2;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = 2;
  matrix.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&matrix, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 0);
  ck_assert_double_eq(res.matrix[0][1], 10);
  ck_assert_double_eq(res.matrix[0][2], -20);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

// matrix 2,2
START_TEST(complements_test_2) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;

  ck_assert_int_eq(s21_calc_complements(&matrix, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 4);
  ck_assert_double_eq(res.matrix[0][1], 0);
  ck_assert_double_eq(res.matrix[1][0], -2);
  ck_assert_double_eq(res.matrix[1][1], 1);
  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

// invalid size
START_TEST(complements_test_3) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(2, 3, &matrix);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[1][0] = 0;
  matrix.matrix[1][1] = 4;

  ck_assert_int_eq(s21_calc_complements(&matrix, &res), 2);
  s21_remove_matrix(&matrix);
}
END_TEST

// matrix 3,3
START_TEST(inverse_test_1) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(3, 3, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[0][2] = 7;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;
  matrix.matrix[1][2] = 4;
  matrix.matrix[2][0] = 5;
  matrix.matrix[2][1] = -2;
  matrix.matrix[2][2] = -3;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &res), 0);
  ck_assert_double_eq(res.matrix[0][0], 1);
  ck_assert_double_eq(res.matrix[0][1], -1);
  ck_assert_double_eq(res.matrix[1][0], -38);
  ck_assert_double_eq(res.matrix[1][1], 41);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

// matrix 2,2
START_TEST(inverse_test_2) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(2, 2, &matrix);
  matrix.matrix[0][0] = 2;
  matrix.matrix[0][1] = 5;
  matrix.matrix[1][0] = 6;
  matrix.matrix[1][1] = 3;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &res), 0);

  ck_assert_double_eq(res.matrix[0][0], -0.125);
  ck_assert_double_eq(res.matrix[0][1], 5.0 / 24);
  ck_assert_double_eq(res.matrix[1][0], 1.0 / 4);
  ck_assert_double_eq(res.matrix[1][1], -1.0 / 12);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

// matrix with 0 determinant
START_TEST(inverse_test_3) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(3, 3, &matrix);
  s21_create_matrix(3, 3, &res);
  matrix.matrix[0][0] = 1;
  matrix.matrix[0][1] = 2;
  matrix.matrix[0][2] = 3;
  matrix.matrix[1][0] = 4;
  matrix.matrix[1][1] = 5;
  matrix.matrix[1][2] = 6;
  matrix.matrix[2][0] = 7;
  matrix.matrix[2][1] = 8;
  matrix.matrix[2][2] = 9;

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &res), 2);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

// invalid size
START_TEST(inverse_test_4) {
  matrix_t matrix;
  matrix_t res;
  s21_create_matrix(3, 2, &matrix);
  s21_create_matrix(3, 2, &res);

  ck_assert_int_eq(s21_inverse_matrix(&matrix, &res), 2);

  s21_remove_matrix(&matrix);
  s21_remove_matrix(&res);
}
END_TEST

Suite *suite_test(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_matrix");
  tc = tcase_create("case_eq");

  tcase_add_test(tc, equal_test_1);
  tcase_add_test(tc, equal_test_2);
  tcase_add_test(tc, equal_test_3);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_create");
  tcase_add_test(tc, create_test_1);
  tcase_add_test(tc, create_test_2);
  tcase_add_test(tc, create_test_3);
  // tcase_add_test(tc, create_test_4);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_sum");
  tcase_add_test(tc, sum_test_1);
  tcase_add_test(tc, sum_test_2);
  tcase_add_test(tc, sum_test_3);
  tcase_add_test(tc, sum_test_4);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_sub");
  tcase_add_test(tc, sub_test_1);
  tcase_add_test(tc, sub_test_2);
  tcase_add_test(tc, sub_test_3);
  tcase_add_test(tc, sub_test_4);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_mult_matrix");
  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);
  tcase_add_test(tc, mult_matrix_test_4);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_mult_number");
  tcase_add_test(tc, mult_number_test_1);
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_transpose");
  tcase_add_test(tc, transpose_test_1);
  tcase_add_test(tc, transpose_test_2);
  tcase_add_test(tc, transpose_test_3);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_determinant");
  tcase_add_test(tc, determinant_test_1);
  tcase_add_test(tc, determinant_test_2);
  tcase_add_test(tc, determinant_test_3);
  tcase_add_test(tc, determinant_test_4);
  tcase_add_test(tc, determinant_test_5);
  // tcase_add_test(tc, determinant_test_6);
  suite_add_tcase(s, tc);

  tc = tcase_create("case_complements");
  tcase_add_test(tc, complements_test_1);
  tcase_add_test(tc, complements_test_2);
  tcase_add_test(tc, complements_test_3);

  suite_add_tcase(s, tc);

  tc = tcase_create("case_inverse");
  tcase_add_test(tc, inverse_test_1);
  tcase_add_test(tc, inverse_test_2);
  tcase_add_test(tc, inverse_test_3);
  tcase_add_test(tc, inverse_test_4);
  // tcase_add_test(tc, inverse_test_5);

  suite_add_tcase(s, tc);

  return s;
}
