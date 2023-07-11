#include "3DViewer.h"

Viewer::Viewer(QWidget* parent) : QOpenGLWidget(parent) {
  get_settings(&settings);
  get_data(filename, &data);
  max_v = get_max_vertexes(data.vertexes, data.count_v * data.size_v);
}

Viewer::~Viewer() { clear_data(&data); }

void Viewer::initializeGL() {
  setWindowTitle("3DViewer_v1.0");
  setGeometry(600, 250, 1000, 1000);
  // Разрешим oengl использовать буфер глубины
  // он хранит в себе расстояние от камеры до объекта отрисовки
  glEnable(GL_DEPTH_TEST);
};

void Viewer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);  // устанавливаем текущую матрицу GL_PROJECTION -
                                // матрица проекции
  glLoadIdentity();  // задаем единичную матрицу
};

void Viewer::paintGL() {
  glClearColor(settings.background_color.r / 255.,
               settings.background_color.g / 255.,
               settings.background_color.b / 255., 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // очистка буфера
  glMatrixMode(GL_MODELVIEW);  // устанавливаем текущую матрицу GL_MODELVIEW -
                               // матрица представления модели
  glLoadIdentity();  // задаем единичную матрицу
  glRotated(mxRot, 1, 0, 0);
  glRotated(myRot, 0, 1, 0);

  // affine transformations
  rotation_x(xRot, &data);
  rotation_y(yRot, &data);
  rotation_z(zRot, &data);
  translated(xShift, yShift, zShift, &data);
  scaled(xScale, yScale, zScale, &data);

  resetParameters();  // сбрасываем параметры чтобы исключить повторное
                      // вращение/сдвиг/масштабирование при перерисовке модели

  if (settings.projection_type == ORTHO) {
    glOrtho(-scale, scale, -scale, scale, -scale, scale);
    if (flag_frustum == 1) {
      translated(0, 0, 2, &data);
      scaled(max_v, max_v, max_v, &data);
      flag_frustum = 0;
    }
  } else {
    glFrustum(-1, 1, -1, 1, 1, 2);
    if (flag_frustum == 0) {
      scaled(1. / max_v, 1. / max_v, 1. / max_v, &data);
      translated(0, 0, -2, &data);
      flag_frustum = 1;
    }
  }

  correction_settings(&settings);
  drawСoordinateSystem();
  drawModel();
};

void Viewer::resetParameters() {
  xRot = 0.;
  yRot = 0.;
  zRot = 0.;

  xShift = 0.;
  yShift = 0.;
  zShift = 0.;

  xScale = 1.;
  yScale = 1.;
  zScale = 1.;
}

void Viewer::drawСoordinateSystem() {
  glLineWidth(CS_LINE_WIDTH);

  glBegin(GL_LINES);
  glColor3d(138 / 255., 0, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(scale / 10, 0, 0);
  glColor3d(0, 138 / 255., 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, scale / 10, 0);
  glColor3d(0, 0, 138 / 255.);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, scale / 10);
  glEnd();
}

void Viewer::drawModel() {
  glVertexPointer(data.size_v, GL_DOUBLE, 0, data.vertexes);
  glEnableClientState(GL_VERTEX_ARRAY);

  drawModelLines();
  drawModelPoints();

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer::drawModelLines() {
  glColor3d(settings.line_color.r / 255., settings.line_color.g / 255.,
            settings.line_color.b / 255.);  // Устанавливаем цвет линий
  glLineWidth(settings.line_width);  // Устанавливаем ширину линий

  if (settings.line_type == DOTTED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);  // Устанавливаем тип линий - пунктир
  }

  for (unsigned i = 0; i < data.count_f; i++) {
    glBegin(GL_LINE_LOOP);
    for (unsigned j = 0; j < data.surfaces[i].size_f; j++) {
      glArrayElement(data.surfaces[i].points[j] - 1);
    }
    glEnd();
  }
  if (settings.line_type == DOTTED) glDisable(GL_LINE_STIPPLE);
}

void Viewer::drawModelPoints() {
  if (settings.vertexes_display_method != NO) {
    (settings.vertexes_display_method == CIRCLE)
        ? glEnable(GL_POINT_SMOOTH)
        : glEnable(GL_PROGRAM_POINT_SIZE);

    glColor3d(settings.vertexes_color.r / 255.,
              settings.vertexes_color.g / 255.,
              settings.vertexes_color.b / 255.);  // Устанавливаем цвет вершин
    glPointSize(settings.vertexes_size);  // Устанавливаем размер точек

    for (unsigned i = 0; i < data.count_f; i++) {
      glBegin(GL_POINTS);
      for (unsigned j = 0; j < data.surfaces[i].size_f; j++) {
        glArrayElement(data.surfaces[i].points[j] - 1);
      }
      glEnd();
    }

    settings.vertexes_display_method == CIRCLE
        ? glDisable(GL_POINT_SMOOTH)
        : glDisable(GL_PROGRAM_POINT_SIZE);
  }
}

void Viewer::redrawModel() {
  clear_data(&data);
  get_data(filename, &data);
  max_v = get_max_vertexes(data.vertexes, data.count_v * data.size_v);
  update();
}

// Запоминаем координату мышки
void Viewer::mousePressEvent(QMouseEvent* mo) { mPos = mo->pos(); }

void Viewer::mouseMoveEvent(QMouseEvent* mo) {
  mxRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  myRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
