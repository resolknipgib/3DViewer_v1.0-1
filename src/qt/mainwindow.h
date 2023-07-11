#ifndef SRC_QT_MAINWINDOW_H_
#define SRC_QT_MAINWINDOW_H_

#include <QComboBox>
#include <QDataStream>
#include <QDockWidget>
#include <QFileDialog>
#include <QGridLayout>
#include <QImage>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QStatusBar>

#include "3DViewer.h"

using namespace std;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Viewer *viewer;

  QMenu *fileMenu;
  QAction *openAct;
  QMenu *saveAsMenu;
  QAction *saveImgAct;
  QAction *saveGifAct;

  QStatusBar *statusBar;
  QDockWidget *dockWidgetParameters;
  QWidget *widget_dwp;
  QGridLayout *layout_dwp;

  QPushButton *buttonUpdate;
  QLabel *label_rot;
  QLineEdit *lineEdit_rotX;
  QLineEdit *lineEdit_rotY;
  QLineEdit *lineEdit_rotZ;
  QLabel *label_shift;
  QLineEdit *lineEdit_shiftX;
  QLineEdit *lineEdit_shiftY;
  QLineEdit *lineEdit_shiftZ;
  QLabel *label_scale;
  QLineEdit *lineEdit_scaleX;
  QLineEdit *lineEdit_scaleY;
  QLineEdit *lineEdit_scaleZ;
  QSlider *slider_scale;
  QPushButton *zoom_area;

  QDockWidget *dockWidgetSettings;
  QWidget *widget_dws;
  QGridLayout *layout_dws;

  QPushButton *buttonApply;
  QLabel *label_background_color;
  QLineEdit *lineEdit_bc_r;
  QLineEdit *lineEdit_bc_g;
  QLineEdit *lineEdit_bc_b;
  QLabel *label_line_color;
  QLineEdit *lineEdit_lc_r;
  QLineEdit *lineEdit_lc_g;
  QLineEdit *lineEdit_lc_b;
  QLineEdit *lineEdit_line_width;
  QComboBox *comboBox_line_type;
  QLabel *label_vertexes_color;
  QLineEdit *lineEdit_vc_r;
  QLineEdit *lineEdit_vc_g;
  QLineEdit *lineEdit_vc_b;
  QLineEdit *lineEdit_vertexes_size;
  QComboBox *comboBox_vertexes_display_method;
  QRadioButton *radioButton_type_ortho;
  QRadioButton *radioButton_type_frustum;

  QPushButton *buttonReset;
  QPushButton *buttonSave;

  void createWidgets();
  void createMenus();
  void createActions();
  void createDockWidgetParameters();
  void createDockWidgetSettings();
  void readSettings();
  void updateStatusBar();

 private slots:
  void openFile();
  void updateModel();
  void applySettings();
  void resetSettings();
  void saveSettings();
  void zoomArea();
  void scaleModel();

  void saveImage();
  void saveGif();
};

int this_positive_number(string str);
int this_number(string str);

#endif  // SRC_QT_MAINWINDOW_H_
