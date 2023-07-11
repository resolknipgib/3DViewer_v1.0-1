#include "parser.h"

void initial_data(data_from_file_obj* data) {
  data->vertexes = NULL;
  data->count_v = 0;
  data->size_v = 3;
  data->surfaces = NULL;
  data->count_f = 0;
}

void get_data(char* const filename, data_from_file_obj* data) {
  initial_data(data);
  FILE* file = fopen(filename, "r");
  if (file) {
    get_total_number(file, data);
    fseek(file, 0, SEEK_SET);
    parser(file, data);
    fclose(file);
  }
}

void get_total_number(FILE* file, data_from_file_obj* data) {
  char line[BUFF_LEN] = {0};
  while (fgets(line, BUFF_LEN, file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      (data->count_v)++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      (data->count_f)++;
    }
  }
}

void parser(FILE* file, data_from_file_obj* data) {
  data->vertexes =
      (double*)malloc(data->count_v * data->size_v * sizeof(double));
  data->surfaces = (polygon*)malloc(data->count_f * sizeof(polygon));
  if (data->vertexes && data->surfaces) {
    unsigned index_v = 0, index_f = 0;
    char line[BUFF_LEN] = {0};
    while (fgets(line, BUFF_LEN, file)) {
      get_vertexes(line, data->vertexes, &index_v);
      get_surfaces(line, data->surfaces, &index_f, data->count_v);
    }
  }
}

void get_vertexes(char* line, double* vertexes, unsigned* index_v) {
  if (*line++ == 'v' && *line == ' ') {
    sscanf(line, "%lf %lf %lf", &vertexes[(*index_v)],
           &vertexes[(*index_v) + 1], &vertexes[(*index_v) + 2]);
    (*index_v) += 3;
  }
}

void get_surfaces(char* line, polygon* surfaces, unsigned* index_f,
                  unsigned count_v) {
  if (*line++ == 'f' && *line++ == ' ') {
    surfaces[*index_f].size_f = get_size_f(line);
    surfaces[*index_f].points =
        (int*)malloc(surfaces[*index_f].size_f * sizeof(int));
    if (surfaces[*index_f].points) {
      for (unsigned i = 0; i < surfaces[*index_f].size_f; i++) {
        get_point(line, &(surfaces[*index_f].points[i]));
        correct_point(&(surfaces[*index_f].points[i]), count_v);
        line = search_next_num(line);
      }
      *index_f += 1;
    }
  }
}

unsigned get_size_f(char* line) {
  unsigned size_f = 0;
  for (int i = 0; *line; i++) {
    if ((*line >= '0' && *line <= '9') || *line == '-') {
      size_f++;
    }
    line = search_next_num(line);
  }
  return size_f;
}

char* search_next_num(char* line) {
  while (*line && *line != ' ') {
    line++;
  }
  if (*line == ' ') line++;
  return line;
}

void get_point(char* line, int* point) {
  if ((*line >= '0' && *line <= '9') || *line == '-') {
    sscanf(line, "%d", point);
  }
}

void correct_point(int* point, unsigned count_v) {
  if (*point < 0) {
    *point += count_v;
  }
}

unsigned get_max_vertexes(double* vertexes, unsigned num_v) {
  unsigned max_v = 1;
  for (unsigned i = 0; i < num_v; i++) {
    if (max_v < fabs(vertexes[i])) max_v = fabs(vertexes[i]);
  }
  return max_v;
}

void clear_data(data_from_file_obj* data) {
  if (data) {
    if (data->vertexes) free(data->vertexes);
    if (data->surfaces) {
      for (unsigned int i = 0; i < data->count_f; i++) {
        free(data->surfaces[i].points);
      }
      free(data->surfaces);
    }
  }
}
