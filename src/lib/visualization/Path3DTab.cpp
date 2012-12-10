/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "visualization/Path3DTab.h"

#include "ui_Path3DTab.h"

#include "sensor/Utils.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Path3DTab::Path3DTab() :
    mUi(new Ui_Path3DTab()),
    mTileMap(
      MapGrid::Coordinate(Utils::minEast, Utils::minNorth),
      MapGrid::Coordinate(Utils::maxEast, Utils::maxNorth),
      MapGrid::Coordinate(Utils::zoomLevels[7] * Utils::pixelWidth,
      Utils::zoomLevels[7] * Utils::pixelHeight)),
    mTextureMap(mTileMap) {
  mUi->setupUi(this);
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  setPointColor(Qt::red);
  setPointSize(1.0);
  setShowPoints(true);
  setSmoothPoints(false);
  setBackgroundColor(Qt::white);
  setFogColor(Qt::white);
  setGroundColor(Qt::lightGray);
}

Path3DTab::~Path3DTab() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Path3DTab::setPointColor(const QColor& color) {
  mPalette.setColor("Point", color);
}

void Path3DTab::setPointSize(double pointSize) {
  mUi->pointSizeSpinBox->setValue(pointSize);
  View3d::getInstance().update();
}

void Path3DTab::setShowPoints(bool showPoints) {
  View3d::getInstance().update();
}

void Path3DTab::setSmoothPoints(bool smoothPoints) {
  mUi->smoothPointsCheckBox->setChecked(smoothPoints);
  View3d::getInstance().update();
}

void Path3DTab::setBackgroundColor(const QColor& color) {
  mPalette.setColor("Background", color);
}

void Path3DTab::setFogColor(const QColor& color) {
  mPalette.setColor("Fog", color);
}

void Path3DTab::setGroundColor(const QColor& color) {
  mPalette.setColor("Ground", color);
}

void Path3DTab::setPath(const PointCloud<>& path) {
  mPointCloud.clear();
  mPointCloud.merge(path);
  double minEast = std::numeric_limits<double>::infinity();
  double maxEast = -std::numeric_limits<double>::infinity();
  double minNorth = std::numeric_limits<double>::infinity();
  double maxNorth = -std::numeric_limits<double>::infinity();
  for (auto it = mPointCloud.getPointBegin(); it != mPointCloud.getPointEnd();
      ++it) {
    if ((*it)(0) < minEast)
      minEast = (*it)(0);
    if ((*it)(0) > maxEast)
      maxEast = (*it)(0);
    if ((*it)(1) < minNorth)
      minNorth = (*it)(1);
    if ((*it)(1) > maxNorth)
      maxNorth = (*it)(1);
  }
  mTextureMap = MapGrid(
    MapGrid::Coordinate(minEast, minNorth),
    MapGrid::Coordinate(maxEast, maxNorth),
    MapGrid::Coordinate(Utils::zoomLevels[7] * Utils::pixelWidth,
    Utils::zoomLevels[7] * Utils::pixelHeight));
  View3d::getInstance().getScene().setTranslation(-mPointCloud[0](0),
    -mPointCloud[0](1), -mPointCloud[0](2));
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Path3DTab::renderBackground() {
  glPushAttrib(GL_CURRENT_BIT);
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopAttrib();
}

void Path3DTab::renderFog(double start, double end, double density) {
  glPushAttrib(GL_CURRENT_BIT);
  QColor color = mPalette.getColor("Fog");
  float colorfv[] = {(float)color.redF(), (float)color.greenF(),
    (float)color.blueF(), 1.0};
  double scale = View3d::getInstance().getScene().getScale();
  double distance = View3d::getInstance().getCamera().getViewpointDistance();
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, colorfv);
  glFogf(GL_FOG_DENSITY, density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, distance + start * scale);
  glFogf(GL_FOG_END, distance + end * scale);
  glPopAttrib();
}

void Path3DTab::renderAxes(double length) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);
  glEnd();
  View3d::getInstance().render(length, 0.0, 0.0, "X", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);
  glEnd();
  View3d::getInstance().render(0.0, length, 0.0, "Y", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);
  glEnd();
  View3d::getInstance().render(0, 0, length, "Z", 0.2 * length, true, true,
    true);
  glPopAttrib();
}

void Path3DTab::renderPoints(double size, bool smooth) {
  glPushAttrib(GL_CURRENT_BIT);
  if (size > 1.0)
    glPointSize(size);
  else
    glPointSize(1.0);
  if (smooth)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  View3d::getInstance().setColor(mPalette, "Point");
  for (auto it = mPointCloud.getPointBegin(); it != mPointCloud.getPointEnd();
      ++it)
//    glVertex3f((*it)(0), (*it)(1), (*it)(2));
    glVertex2f((*it)(0), (*it)(1));
  glEnd();
  glPointSize(1.0);
  glDisable(GL_POINT_SMOOTH);
  glPopAttrib();
}

void Path3DTab::renderTiles() {
  const auto resolution = mTextureMap.getResolution();
  const auto halfRes = resolution / 2;
  for (MapGrid::Index i = MapGrid::Index::Zero();
      i != mTextureMap.getNumCells(); mTextureMap.incrementIndex(i)) {
    const auto index = mTileMap.getIndex(mTextureMap.getCoordinates(i));
    const auto coordinate = mTileMap.getCoordinates(index);
    if (mTextureMap[i] == 0) {
      std::string tileFile = "maps/" +
        Utils::downloadMapTile(coordinate(0), coordinate(1),
        Utils::zoomLevels[7],
        "maps", Utils::pixelWidth, Utils::pixelHeight, Utils::MapType::aerial,
        Utils::MapFormat::png);
      QImage tileImage(tileFile.c_str());
      QImage tileImageTrans = tileImage.mirrored();
      GLuint textureID = View3d::getInstance().bindTexture(tileImageTrans);
      mTextureMap[i] = textureID;
    }
    const auto upperLeft = coordinate - halfRes;
    View3d::getInstance().drawTexture(QRectF(upperLeft(0),
      upperLeft(1), resolution(0), resolution(1)), mTextureMap[i]);
  }
}

void Path3DTab::render(View3d& view, Scene3d& Scene3d) {
  renderBackground();
  //glEnable(GL_FOG);
  //renderFog(10, 2.0 * 10, 1.0);
  renderAxes(2.5);
  renderPoints(mUi->pointSizeSpinBox->value(),
    mUi->smoothPointsCheckBox->isChecked());
  renderTiles();
}

void Path3DTab::colorChanged(const QString& role, const QColor& color) {
  View3d::getInstance().update();
}

void Path3DTab::pointSizeChanged(double pointSize) {
  setPointSize(pointSize);
}

void Path3DTab::smoothPointsToggled(bool checked) {
  setSmoothPoints(checked);
}
