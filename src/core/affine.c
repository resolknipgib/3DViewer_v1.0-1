#include "affine.h"

void mul_3x3(double M[3][3], double *vertexes) {
  double vector[3] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      vector[i] += M[i][j] * vertexes[j];
    }
  }
  for (int i = 0; i < 3; i++) {
    vertexes[i] = vector[i];
  }
}

void rotation_x(double teta, data_from_file_obj *data) {
  if (teta) {
    double Rx[3][3] = {0};
    create_matrix_Rx(Rx, teta);
    for (unsigned i = 0, j = 0; i < data->count_v; i++, j += data->size_v) {
      mul_3x3(Rx, &data->vertexes[j]);
    }
  }
}

void create_matrix_Rx(double Rx[3][3], double teta) {
  teta *= M_PI / 180;
  Rx[0][0] = 1;
  Rx[0][1] = 0;
  Rx[0][2] = 0;
  Rx[1][0] = 0;
  Rx[1][1] = cos(teta);
  Rx[1][2] = -sin(teta);
  Rx[2][0] = 0;
  Rx[2][1] = sin(teta);
  Rx[2][2] = cos(teta);
}

void rotation_y(double psi, data_from_file_obj *data) {
  if (psi) {
    double Ry[3][3] = {0};
    create_matrix_Ry(Ry, psi);
    for (unsigned i = 0, j = 0; i < data->count_v; i++, j += data->size_v) {
      mul_3x3(Ry, &data->vertexes[j]);
    }
  }
}

void create_matrix_Ry(double Ry[3][3], double psi) {
  psi *= M_PI / 180;
  Ry[0][0] = cos(psi);
  Ry[0][1] = 0;
  Ry[0][2] = sin(psi);
  Ry[1][0] = 0;
  Ry[1][1] = 1;
  Ry[1][2] = 0;
  Ry[2][0] = -sin(psi);
  Ry[2][1] = 0;
  Ry[2][2] = cos(psi);
}

void rotation_z(double fi, data_from_file_obj *data) {
  if (fi) {
    double Rz[3][3] = {0};
    create_matrix_Rz(Rz, fi);
    for (unsigned i = 0, j = 0; i < data->count_v; i++, j += data->size_v) {
      mul_3x3(Rz, &data->vertexes[j]);
    }
  }
}

void create_matrix_Rz(double Rz[3][3], double fi) {
  fi *= M_PI / 180;
  Rz[0][0] = cos(fi);
  Rz[0][1] = -sin(fi);
  Rz[0][2] = 0;
  Rz[1][0] = sin(fi);
  Rz[1][1] = cos(fi);
  Rz[1][2] = 0;
  Rz[2][0] = 0;
  Rz[2][1] = 0;
  Rz[2][2] = 1;
}

void translated(double x, double y, double z, data_from_file_obj *data) {
  if (x || y || z) {
    for (unsigned i = 0, j = 0; i < data->count_v; i++) {
      data->vertexes[j++] += x;
      data->vertexes[j++] += y;
      data->vertexes[j++] += z;
    }
  }
}

void scaled(double x, double y, double z, data_from_file_obj *data) {
  if (x != 1. || y != 1. || z != 1.) {
    if (x == 0) x = 0.001;
    if (y == 0) y = 0.001;
    if (z == 0) z = 0.001;
    for (unsigned i = 0, j = 0; i < data->count_v; i++) {
      data->vertexes[j++] *= x;
      data->vertexes[j++] *= y;
      data->vertexes[j++] *= z;
    }
  }
}
