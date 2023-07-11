#include "mainwindow.h"

#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  this->resize(1200, 1000);

  createWidgets();
  createActions();
  createMenus();
  createDockWidgetParameters();
  createDockWidgetSettings();

  readSettings();

  setCentralWidget(viewer);
  setStatusBar(statusBar);
  addDockWidget(Qt::RightDockWidgetArea, dockWidgetParameters);
  addDockWidget(Qt::RightDockWidgetArea, dockWidgetSettings);
}

MainWindow::~MainWindow() {
  delete layout_dwp;
  delete layout_dws;
}

void MainWindow::createWidgets() {
  viewer = new Viewer(this);

  statusBar = new QStatusBar();
  buttonUpdate = new QPushButton("Update", this);
  label_rot = new QLabel("rotation (x, y, z):", this);
  lineEdit_rotX = new QLineEdit("0", this);
  lineEdit_rotY = new QLineEdit("0", this);
  lineEdit_rotZ = new QLineEdit("0", this);
  label_shift = new QLabel("shift (x, y, z):", this);
  lineEdit_shiftX = new QLineEdit("0", this);
  lineEdit_shiftY = new QLineEdit("0", this);
  lineEdit_shiftZ = new QLineEdit("0", this);
  label_scale = new QLabel("scale (x, y, z):", this);
  lineEdit_scaleX = new QLineEdit("1", this);
  lineEdit_scaleY = new QLineEdit("1", this);
  lineEdit_scaleZ = new QLineEdit("1", this);
  slider_scale = new QSlider(Qt::Horizontal, this);
  slider_scale->setValue(viewer->scale);
  slider_scale->setMinimum(1);
  slider_scale->setMaximum(2 * viewer->scale);
  zoom_area = new QPushButton("x2", this);

  label_background_color = new QLabel("background color (r, g, b):", this);
  lineEdit_bc_r = new QLineEdit(this);
  lineEdit_bc_g = new QLineEdit(this);
  lineEdit_bc_b = new QLineEdit(this);
  label_line_color = new QLabel("line color (r, g, b):", this);
  lineEdit_lc_r = new QLineEdit(this);
  lineEdit_lc_g = new QLineEdit(this);
  lineEdit_lc_b = new QLineEdit(this);
  lineEdit_line_width = new QLineEdit(this);
  comboBox_line_type = new QComboBox(this);
  comboBox_line_type->insertItem(0, "Solid");
  comboBox_line_type->insertItem(1, "Dotted");
  label_vertexes_color = new QLabel("vertexes color (r, g, b):", this);
  lineEdit_vc_r = new QLineEdit(this);
  lineEdit_vc_g = new QLineEdit(this);
  lineEdit_vc_b = new QLineEdit(this);
  lineEdit_vertexes_size = new QLineEdit(this);
  comboBox_vertexes_display_method = new QComboBox(this);
  comboBox_vertexes_display_method->insertItem(0, "No");
  comboBox_vertexes_display_method->insertItem(1, "Circle");
  comboBox_vertexes_display_method->insertItem(2, "Square");
  buttonApply = new QPushButton("Apply", this);
  radioButton_type_ortho = new QRadioButton("Ortho", this);
  radioButton_type_frustum = new QRadioButton("Frustum", this);

  buttonReset = new QPushButton("Reset", this);
  buttonSave = new QPushButton("Save", this);

  connect(buttonUpdate, &QPushButton::clicked, this, &MainWindow::updateModel);
  connect(buttonApply, &QPushButton::clicked, this, &MainWindow::applySettings);
  connect(buttonReset, &QPushButton::clicked, this, &MainWindow::resetSettings);
  connect(buttonSave, &QPushButton::clicked, this, &MainWindow::saveSettings);
  connect(zoom_area, &QPushButton::clicked, this, &MainWindow::zoomArea);
  connect(slider_scale, &QSlider::valueChanged, this, &MainWindow::scaleModel);
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(openAct);
  saveAsMenu = fileMenu->addMenu(tr("Save as..."));
  saveAsMenu->addAction(saveImgAct);
  saveAsMenu->addAction(saveGifAct);
}

void MainWindow::createActions() {
  openAct = new QAction(tr("Open file"), this);
  openAct->setStatusTip(tr("Open File"));
  connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

  saveImgAct = new QAction(tr("image"), this);
  saveImgAct->setStatusTip(tr("Save an image to a file in bmp or jpeg format"));
  connect(saveImgAct, &QAction::triggered, this, &MainWindow::saveImage);

  saveGifAct = new QAction(tr("gif"), this);
  saveGifAct->setStatusTip(tr("Record \"screencasts\""));
  connect(saveGifAct, &QAction::triggered, this, &MainWindow::saveGif);
}

void MainWindow::createDockWidgetParameters() {
  dockWidgetParameters = new QDockWidget(tr("Display parameters"), this);
  dockWidgetParameters->setMaximumWidth(250);
  widget_dwp = new QWidget(this);
  layout_dwp = new QGridLayout(widget_dwp);

  layout_dwp->addWidget(label_rot, 0, 0, 1, 3);
  layout_dwp->addWidget(lineEdit_rotX, 1, 0);
  layout_dwp->addWidget(lineEdit_rotY, 1, 1);
  layout_dwp->addWidget(lineEdit_rotZ, 1, 2);
  layout_dwp->addWidget(label_shift, 2, 0, 1, 3);
  layout_dwp->addWidget(lineEdit_shiftX, 3, 0);
  layout_dwp->addWidget(lineEdit_shiftY, 3, 1);
  layout_dwp->addWidget(lineEdit_shiftZ, 3, 2);
  layout_dwp->addWidget(label_scale, 4, 0, 1, 3);
  layout_dwp->addWidget(lineEdit_scaleX, 5, 0);
  layout_dwp->addWidget(lineEdit_scaleY, 5, 1);
  layout_dwp->addWidget(lineEdit_scaleZ, 5, 2);

  layout_dwp->addWidget(buttonUpdate, 6, 1, 1, 2);
  layout_dwp->addWidget(slider_scale, 7, 0, 1, 3);
  layout_dwp->addWidget(zoom_area, 8, 2);

  layout_dwp->setRowStretch(9, 10);  // коэффициент растяжения 9-й строки
  dockWidgetParameters->setWidget(widget_dwp);
}

void MainWindow::createDockWidgetSettings() {
  dockWidgetSettings = new QDockWidget(tr("Display settings"), this);
  dockWidgetSettings->setMaximumWidth(250);
  widget_dws = new QWidget(this);
  layout_dws = new QGridLayout(widget_dws);

  layout_dws->addWidget(label_background_color, 0, 0, 1, 3);
  layout_dws->addWidget(lineEdit_bc_r, 1, 0);
  layout_dws->addWidget(lineEdit_bc_g, 1, 1);
  layout_dws->addWidget(lineEdit_bc_b, 1, 2);

  layout_dws->addWidget(label_line_color, 2, 0, 1, 3);
  layout_dws->addWidget(lineEdit_lc_r, 3, 0);
  layout_dws->addWidget(lineEdit_lc_g, 3, 1);
  layout_dws->addWidget(lineEdit_lc_b, 3, 2);
  layout_dws->addWidget(new QLabel("width:", this), 4, 0);
  layout_dws->addWidget(lineEdit_line_width, 4, 1);
  layout_dws->addWidget(new QLabel("type:", this), 5, 0);
  layout_dws->addWidget(comboBox_line_type, 5, 1, 1, 2);

  layout_dws->addWidget(label_vertexes_color, 6, 0, 1, 3);
  layout_dws->addWidget(lineEdit_vc_r, 7, 0);
  layout_dws->addWidget(lineEdit_vc_g, 7, 1);
  layout_dws->addWidget(lineEdit_vc_b, 7, 2);
  layout_dws->addWidget(new QLabel("size:", this), 8, 0);
  layout_dws->addWidget(lineEdit_vertexes_size, 8, 1);
  layout_dws->addWidget(new QLabel("display:", this), 9, 0);
  layout_dws->addWidget(comboBox_vertexes_display_method, 9, 1, 1, 2);

  layout_dws->addWidget(radioButton_type_ortho, 10, 1);
  layout_dws->addWidget(radioButton_type_frustum, 10, 2);
  layout_dws->addWidget(buttonApply, 11, 0);
  layout_dws->addWidget(buttonReset, 11, 1);
  layout_dws->addWidget(buttonSave, 11, 2);

  layout_dws->setRowStretch(12, 10);  // коэффициент растяжения 12-й строки
  dockWidgetSettings->setWidget(widget_dws);
}

void MainWindow::readSettings() {
  lineEdit_bc_r->setText(QString::number(viewer->settings.background_color.r));
  lineEdit_bc_g->setText(QString::number(viewer->settings.background_color.g));
  lineEdit_bc_b->setText(QString::number(viewer->settings.background_color.b));
  lineEdit_lc_r->setText(QString::number(viewer->settings.line_color.r));
  lineEdit_lc_g->setText(QString::number(viewer->settings.line_color.g));
  lineEdit_lc_b->setText(QString::number(viewer->settings.line_color.b));
  lineEdit_line_width->setText(QString::number(viewer->settings.line_width));
  comboBox_line_type->setCurrentIndex(viewer->settings.line_type);
  lineEdit_vc_r->setText(QString::number(viewer->settings.vertexes_color.r));
  lineEdit_vc_g->setText(QString::number(viewer->settings.vertexes_color.g));
  lineEdit_vc_b->setText(QString::number(viewer->settings.vertexes_color.b));
  lineEdit_vertexes_size->setText(
      QString::number(viewer->settings.vertexes_size));

  comboBox_vertexes_display_method->setCurrentIndex(
      viewer->settings.vertexes_display_method);

  viewer->settings.projection_type == ORTHO
      ? radioButton_type_ortho->setChecked(true)
      : radioButton_type_frustum->setChecked(true);
}

void MainWindow::updateStatusBar() {
  char buff_status_Bar[BUFF_LEN] = {0};
  sprintf(buff_status_Bar, "file: %s, v %d, f %d", viewer->filename,
          viewer->data.count_v, viewer->data.count_f);
  statusBar->showMessage(tr(buff_status_Bar));
}

void MainWindow::updateModel() {
  if (this_number(lineEdit_rotX->text().toStdString()))
    viewer->xRot = stod(lineEdit_rotX->text().toStdString());
  if (this_number(lineEdit_rotY->text().toStdString()))
    viewer->yRot = stod(lineEdit_rotY->text().toStdString());
  if (this_number(lineEdit_rotZ->text().toStdString()))
    viewer->zRot = stod(lineEdit_rotZ->text().toStdString());

  if (this_number(lineEdit_shiftX->text().toStdString()))
    viewer->xShift = stod(lineEdit_shiftX->text().toStdString());
  if (this_number(lineEdit_shiftY->text().toStdString()))
    viewer->yShift = stod(lineEdit_shiftY->text().toStdString());
  if (this_number(lineEdit_shiftZ->text().toStdString()))
    viewer->zShift = stod(lineEdit_shiftZ->text().toStdString());

  if (this_number(lineEdit_scaleX->text().toStdString()))
    viewer->xScale = stod(lineEdit_scaleX->text().toStdString());
  if (this_number(lineEdit_scaleY->text().toStdString()))
    viewer->yScale = stod(lineEdit_scaleY->text().toStdString());
  if (this_number(lineEdit_scaleZ->text().toStdString()))
    viewer->zScale = stod(lineEdit_scaleZ->text().toStdString());

  viewer->update();
  updateStatusBar();
}

void MainWindow::applySettings() {
  viewer->settings.line_type = (LineType)comboBox_line_type->currentIndex();
  if (this_positive_number(lineEdit_lc_r->text().toStdString()))
    viewer->settings.line_color.r = stod(lineEdit_lc_r->text().toStdString());
  if (this_positive_number(lineEdit_lc_g->text().toStdString()))
    viewer->settings.line_color.g = stod(lineEdit_lc_g->text().toStdString());
  if (this_positive_number(lineEdit_lc_b->text().toStdString()))
    viewer->settings.line_color.b = stod(lineEdit_lc_b->text().toStdString());
  if (this_positive_number(lineEdit_line_width->text().toStdString()))
    viewer->settings.line_width =
        stod(lineEdit_line_width->text().toStdString());
  viewer->settings.vertexes_display_method =
      (VertexesDisplayMethod)comboBox_vertexes_display_method->currentIndex();
  if (this_positive_number(lineEdit_vc_r->text().toStdString()))
    viewer->settings.vertexes_color.r =
        stod(lineEdit_vc_r->text().toStdString());
  if (this_positive_number(lineEdit_vc_g->text().toStdString()))
    viewer->settings.vertexes_color.g =
        stod(lineEdit_vc_g->text().toStdString());
  if (this_positive_number(lineEdit_vc_b->text().toStdString()))
    viewer->settings.vertexes_color.b =
        stod(lineEdit_vc_b->text().toStdString());
  if (this_positive_number(lineEdit_vertexes_size->text().toStdString()))
    viewer->settings.vertexes_size =
        stod(lineEdit_vertexes_size->text().toStdString());
  if (this_positive_number(lineEdit_bc_r->text().toStdString()))
    viewer->settings.background_color.r =
        stod(lineEdit_bc_r->text().toStdString());
  if (this_positive_number(lineEdit_bc_g->text().toStdString()))
    viewer->settings.background_color.g =
        stod(lineEdit_bc_g->text().toStdString());
  if (this_positive_number(lineEdit_bc_b->text().toStdString()))
    viewer->settings.background_color.b =
        stod(lineEdit_bc_b->text().toStdString());
  radioButton_type_ortho->isChecked() == true
      ? viewer->settings.projection_type = ORTHO
      : viewer->settings.projection_type = FRUSTUM;

  viewer->update();
}

void MainWindow::openFile() {
  QString fileName = QFileDialog::getOpenFileName(this);
  strcpy(viewer->filename, (char *)(fileName.toStdString().c_str()));
  viewer->redrawModel();

  updateStatusBar();
  viewer->scale = BASIC_SCALE;
  slider_scale->setMaximum(2 * viewer->scale);
}

void MainWindow::resetSettings() {
  get_settings(&viewer->settings);
  readSettings();
  viewer->update();
}

void MainWindow::saveSettings() { save_settings(&viewer->settings); }

void MainWindow::zoomArea() {
  viewer->scale *= 2;
  slider_scale->setMaximum(2 * viewer->scale);
  viewer->update();
}

void MainWindow::scaleModel() {
  viewer->scale = slider_scale->sliderPosition();
  viewer->update();
}

void MainWindow::saveImage() {
  QImage image(centralWidget()->size(), QImage::Format_ARGB32);
  image.fill(0);
  centralWidget()->render(&image, QPoint(), QRegion(), QWidget::DrawChildren);

  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                  tr("*.bmp;;*.jpeg"));

  if (fileName != nullptr) {
    char name[BUFF_LEN] = {0};
    strcpy(name, fileName.toStdString().c_str());
    int i = BUFF_LEN;
    while (i > 0 && name[i] != '.') i--;
    name[i + 1] == 'j' ? image.save(fileName, "JPEG")
                       : image.save(fileName, "BMP");
  }
}

void MainWindow::saveGif() {
  // QString fileName =
  //     QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("*.gif"));
  // const char *filename = (const char *)fileName.toStdString().c_str();
  // const int width = 640;
  // const int height = 480;
  // // uint8_t image[width * height * 4];

  // if (filename != nullptr) {
  //   QImage image(centralWidget()->size(), QImage::Format_ARGB32);
  //   centralWidget()->render(&image, QPoint(), QRegion(),
  //   QWidget::DrawChildren);

  //   QByteArray data;
  //   QBuffer buffer(&data);
  //   buffer.open(QIODevice::WriteOnly);
  //   image.save(&buffer, "PNG");
  //   QDataStream stream(&buffer);

  //   GifWriter writer = {};
  //   GifBegin(&writer, filename, width, height, 2, 8, true);

  //   // GifWriteFrame(&writer, (const uint8_t *)image.bits(), width, height,
  //   2,
  //   // 8,
  //   //               true);

  //   GifEnd(&writer);
  // }
}

int this_positive_number(string str) { return str[0] >= '0' && str[0] <= '9'; }

int this_number(string str) {
  return str[0] == '-' ? this_positive_number(&str[1])
                       : this_positive_number(str);
}
