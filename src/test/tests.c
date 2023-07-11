#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../core/affine.h"
#include "../core/parser.h"
#include "../core/settings.h"
data_from_file_obj data;
data_from_file_obj res;

START_TEST(test_1) {
  get_data("test/wolf.obj", &data);
  ck_assert_int_eq(79473, data.count_v);
  clear_data(&data);
}
END_TEST

START_TEST(test_2) {
  get_data("test/wolf.obj", &data);
  ck_assert_int_eq(79280, data.count_f);
  clear_data(&data);
}
END_TEST

START_TEST(scaled_1) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  scaled(1, 1, 1, &data);
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(scaled_2) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  scaled(3, 3, 3, &data);
  for (unsigned int j = 0; j < data.count_v * data.size_v; j++) {
    res.vertexes[j] *= 3;
  }
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(scaled_3) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  scaled(0, 0, 0, &data);
  for (unsigned int j = 0; j < data.count_v * data.size_v; j++) {
    res.vertexes[j] *= 0.001;
  }
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(translated_1) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  translated(0, 0, 0, &data);
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(translated_2) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  translated(3, 3, 3, &data);
  for (unsigned int j = 0; j < data.count_v * data.size_v; j++) {
    res.vertexes[j] += 3;
  }
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(translated_3) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  translated(1, 1, 1, &data);
  for (unsigned int j = 0; j < data.count_v * data.size_v; j++) {
    res.vertexes[j] += 1;
  }
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }
  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(rotation_X) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  rotation_x(0, &data);
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }

  rotation_x(2, &data);

  ck_assert_double_eq_tol(data.vertexes[0], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[1], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[2], -0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[3], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[4], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[5], -1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[6], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[7], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[8], 1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[9], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[10], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[11], 0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[12], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[13], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[14], -0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[15], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[16], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[17], -1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[18], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[19], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[20], 1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[21], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[22], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[23], 0.964491, 1e-6);

  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(rotation_Y) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  rotation_y(0, &data);
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }

  rotation_y(2, &data);

  ck_assert_double_eq_tol(data.vertexes[0], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[1], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[2], -1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[3], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[4], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[5], -1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[6], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[7], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[8], 0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[9], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[10], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[11], 0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[12], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[13], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[14], -0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[15], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[16], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[17], -0.964491, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[18], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[19], 1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[20], 1.034290, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[21], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[22], -1, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[23], 1.034290, 1e-6);

  clear_data(&data);
  clear_data(&res);
}
END_TEST

START_TEST(rotation_Z) {
  get_data("test/test.obj", &data);
  get_data("test/test.obj", &res);
  rotation_z(0, &data);
  for (unsigned int i = 0; i < data.count_v * data.size_v; i++) {
    ck_assert_double_eq(data.vertexes[i], res.vertexes[i]);
  }

  rotation_z(2, &data);

  ck_assert_double_eq_tol(data.vertexes[0], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[1], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[2], -1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[3], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[4], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[5], -1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[6], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[7], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[8], 1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[9], 1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[10], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[11], 1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[12], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[13], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[14], -1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[15], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[16], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[17], -1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[18], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[19], 0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[20], 1, 1e-6);

  ck_assert_double_eq_tol(data.vertexes[21], -0.964491, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[22], -1.034290, 1e-6);
  ck_assert_double_eq_tol(data.vertexes[23], 1, 1e-6);

  clear_data(&data);
  clear_data(&res);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc);

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);

  tcase_add_test(tc, scaled_1);
  tcase_add_test(tc, scaled_2);
  tcase_add_test(tc, scaled_3);

  tcase_add_test(tc, translated_1);
  tcase_add_test(tc, translated_2);
  tcase_add_test(tc, translated_3);

  tcase_add_test(tc, rotation_X);
  tcase_add_test(tc, rotation_Y);
  tcase_add_test(tc, rotation_Z);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
