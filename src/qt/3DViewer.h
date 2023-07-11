#ifndef SRC_QT_3DVIEWER_H_
#define SRC_QT_3DVIEWER_H_

#include <QMouseEvent>
#include <QOpenGLWidget>

extern "C" {
#include "../core/affine.h"
#include "../core/parser.h"
#include "../core/settings.h"
}

#define BASIC_SCALE 50.
#define CS_LINE_WIDTH 5

class Viewer : public QOpenGLWidget {
  Q_OBJECT
 public:
  Viewer(QWidget* parent = nullptr);
  ~Viewer();

  double xRot = 0., yRot = 0., zRot = 0.;
  double xShift = 0., yShift = 0., zShift = 0.;
  double xScale = 1., yScale = 1., zScale = 1.;
  double scale = BASIC_SCALE;
  char filename[BUFF_LEN] = {0};
  data_from_file_obj data;
  DisplaySettings settings;

  void redrawModel();

 private:
  QPoint mPos;
  double mxRot, myRot;
  int flag_frustum = 0;
  unsigned max_v = 1;

  void drawСoordinateSystem();
  void drawModel();
  void drawModelLines();
  void drawModelPoints();
  void resetParameters();

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  // функция вызывается при нажатии мышки
  void mousePressEvent(QMouseEvent* mo) override;
  // функция вызвывается при движении мышки
  void mouseMoveEvent(QMouseEvent* mo) override;
};

#endif  // SRC_QT_3DVIEWER_H_