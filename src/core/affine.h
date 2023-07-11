#ifndef SRC_CORE_AFFINE_H_
#define SRC_CORE_AFFINE_H_

#include <math.h>
#include <stdio.h>

#include "parser.h"

void mul_3x3(double M[3][3], double *vertexes);
void rotation_x(double teta, data_from_file_obj *data);
void create_matrix_Rx(double Rx[3][3], double teta);
void rotation_y(double psi, data_from_file_obj *data);
void create_matrix_Ry(double Ry[3][3], double psi);
void rotation_z(double fi, data_from_file_obj *data);
void create_matrix_Rz(double Rz[3][3], double fi);
void translated(double x, double y, double z, data_from_file_obj *data);
void scaled(double x, double y, double z, data_from_file_obj *data);

#endif  // SRC_CORE_AFFINE_H_
