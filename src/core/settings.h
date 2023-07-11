#ifndef SRC_CORE_SETTINGS_H_
#define SRC_CORE_SETTINGS_H_

#define BUFF_LEN 200

// Тип проекции
enum ProjectionType { ORTHO, FRUSTUM };
// Тип ребер
enum LineType { SOLID, DOTTED };
// Способ отображения вершин
enum VertexesDisplayMethod { NO, CIRCLE, SQUARE };

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Color;

typedef struct {
  enum ProjectionType projection_type;
  enum LineType line_type;
  Color line_color;
  unsigned line_width;
  enum VertexesDisplayMethod vertexes_display_method;
  Color vertexes_color;
  unsigned vertexes_size;
  Color background_color;
} DisplaySettings;

void get_settings(DisplaySettings* settings);
void initial_settings(DisplaySettings* settings);
void read_settings(DisplaySettings* settings);
void correction_settings(DisplaySettings* settings);

void save_settings(DisplaySettings* settings);

#endif  // SRC_CORE_SETTINGS_H_
