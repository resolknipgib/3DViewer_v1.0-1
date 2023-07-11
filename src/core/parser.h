#ifndef SRC_CORE_PARSER_H_
#define SRC_CORE_PARSER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_LEN 200

typedef struct {
  int* points;
  unsigned size_f;
} polygon;

typedef struct {
  double* vertexes;
  unsigned count_v;
  unsigned size_v;
  polygon* surfaces;
  unsigned count_f;
} data_from_file_obj;

void initial_data(data_from_file_obj* data);
void get_data(char* const filename, data_from_file_obj* data);

void get_total_number(FILE* file, data_from_file_obj* data);
void parser(FILE* file, data_from_file_obj* data);
void get_vertexes(char* line, double* vertexes, unsigned* index_v);
void get_surfaces(char* line, polygon* surfaces, unsigned* index_f,
                  unsigned count_v);

unsigned get_size_f(char* line);
char* search_next_num(char* line);
void get_point(char* line, int* point);
void correct_point(int* point, unsigned count_v);

unsigned get_max_vertexes(double* vertexes, unsigned num_v);

void clear_data(data_from_file_obj* data);
void clear_vertexes(double* vertexes);
void clear_surfaces(polygon* surfaces);

#endif  // SRC_CORE_PARSER_H_
