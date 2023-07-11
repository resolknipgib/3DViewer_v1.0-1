#include "settings.h"

#include <stdio.h>

void get_settings(DisplaySettings* settings) {
  initial_settings(settings);
  read_settings(settings);
  correction_settings(settings);
}

void initial_settings(DisplaySettings* settings) {
  settings->projection_type = ORTHO;
  settings->line_type = SOLID;
  settings->line_color.r = 244;
  settings->line_color.g = 164;
  settings->line_color.b = 96;
  settings->line_width = 1;
  settings->vertexes_display_method = CIRCLE;
  settings->vertexes_color.r = 0;
  settings->vertexes_color.g = 0;
  settings->vertexes_color.b = 0;
  settings->vertexes_size = 3;
  settings->background_color.r = 192;
  settings->background_color.g = 192;
  settings->background_color.b = 192;
}

void read_settings(DisplaySettings* settings) {
  FILE* file = fopen("./settings.conf", "r");
  if (file) {
    char line[BUFF_LEN] = {0};
    // projection_type
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %d", (int*)&settings->projection_type);
    // line_type
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %d", (int*)&settings->line_type);
    // line_color
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %hhu %hhu %hhu", &settings->line_color.r,
           &settings->line_color.g, &settings->line_color.b);
    // line_width
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %d", (int*)&settings->line_width);
    // vertexes_display_method
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %d", (int*)&settings->vertexes_display_method);
    // vertexes_color
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %hhu %hhu %hhu", &settings->vertexes_color.r,
           &settings->vertexes_color.g, &settings->vertexes_color.b);
    // vertexes_size
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %d", (int*)&settings->vertexes_size);
    // background_color
    fgets(line, BUFF_LEN, file);
    sscanf(line, "%*s %hhu %hhu %hhu", &settings->background_color.r,
           &settings->background_color.g, &settings->background_color.b);

    fclose(file);
  }
}

void correction_settings(DisplaySettings* settings) {
  if (settings->projection_type != ORTHO &&
      settings->projection_type != FRUSTUM)
    settings->projection_type = ORTHO;

  if (settings->line_type != SOLID && settings->line_type != DOTTED)
    settings->line_type = SOLID;

  if (settings->vertexes_display_method != NO &&
      settings->vertexes_display_method != CIRCLE &&
      settings->vertexes_display_method != SQUARE) {
    settings->vertexes_display_method = CIRCLE;
  }
}

void save_settings(DisplaySettings* settings) {
  FILE* file = fopen("./settings.conf", "w");
  fprintf(
      file,
      "projection_type: %d\nline_type: %d\nline_color: %d %d %d\nline_width: "
      "%d\nvertexes_display_method: %d\nvertexes_color: %d %d "
      "%d\nvertexes_size: "
      "%d\nbackground_color: %d %d %d\n",
      settings->projection_type, settings->line_type, settings->line_color.r,
      settings->line_color.g, settings->line_color.b, settings->line_width,
      settings->vertexes_display_method, settings->vertexes_color.r,
      settings->vertexes_color.g, settings->vertexes_color.b,
      settings->vertexes_size, settings->background_color.r,
      settings->background_color.g, settings->background_color.b);
  fclose(file);
}
