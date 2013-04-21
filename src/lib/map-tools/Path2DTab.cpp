/******************************************************************************
 * Copyright (C) 2012 by Jerome Maye                                          *
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

#include "map-tools/Path2DTab.h"

#include <iostream>
#include <sstream>

#include <QtCore/QDir>
#include <QtGui/QFileDialog>

#include "map-tools/View2d.h"
#include "map-tools/Tools.h"
#include "sensor/Utils.h"

#include "ui_Path2DTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Path2DTab::Path2DTab() :
    mUi(new Ui_Path2DTab()),
    mCanvasDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3.0 * Tools::pixelWidth,
      3 * Tools::pixelHeight),
      DisplayGrid::Coordinate((double)Tools::pixelWidth,
      Tools::pixelHeight)),
    mSymMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3.0 * Tools::pixelWidth,
      3 * Tools::pixelHeight),
      DisplayGrid::Coordinate((double)Tools::pixelWidth,
      Tools::pixelHeight)),
    mAerialMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3.0 * Tools::pixelWidth,
      3 * Tools::pixelHeight),
      DisplayGrid::Coordinate((double)Tools::pixelWidth,
      Tools::pixelHeight)),
    mInfoMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3.0 * Tools::pixelWidth,
      3 * Tools::pixelHeight),
      DisplayGrid::Coordinate((double)Tools::pixelWidth,
      Tools::pixelHeight)) {
  mUi->setupUi(this);
  setMapFolder(QDir::current().path());
  mMapGrids.clear();
  for (size_t i = 0; i < Tools::zoomLevels.size(); ++i)
    mMapGrids.push_back(MapGrid(
      MapGrid::Coordinate(Tools::minEast, Tools::minNorth),
      MapGrid::Coordinate(Tools::maxEast, Tools::maxNorth),
      MapGrid::Coordinate(Tools::zoomLevels[i] * Tools::pixelWidth,
      Tools::zoomLevels[i] * Tools::pixelHeight)));
//  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
//      i != mCanvasDisplay.getNumCells(); mCanvasDisplay.incrementIndex(i)) {
//    const auto coordinate = mCanvasDisplay.getCoordinates(i) -
//      DisplayGrid::Coordinate(Tools::pixelWidth / 2.0,
//      Tools::pixelHeight / 2.0);
//    mCanvasDisplay[i] = View2d::getInstance().getScene().addRect(
//      coordinate(0), coordinate(1), Tools::pixelWidth,
//      Tools::pixelHeight);
//    std::stringstream number;
//    number << "(" << i(0) << ", " << i(1) << ")";
//    QGraphicsSimpleTextItem* text = 
//      View2d::getInstance().getScene().addSimpleText(number.str().c_str());
//    text->setPos(mCanvasDisplay.getCoordinates(i)(0),
//      3 * Tools::pixelHeight - mCanvasDisplay.getCoordinates(i)(1));
//  }
}

Path2DTab::~Path2DTab() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Path2DTab::setMapFolder(const QString& folderName) {
  mUi->folderEdit->setText(folderName);
}

void Path2DTab::setSliderPosition(int pos) {
  mUi->zoomSlider->setSliderPosition(pos);
}

void Path2DTab::setPath(const PointCloud<>& path) {
  for (size_t i = 0; i < Tools::zoomLevels.size(); ++i) {
    for (auto it = path.getPointBegin(); it != path.getPointEnd();
        ++it) {
      PointCloud<>& pointcloud =
        mMapGrids[i](MapGrid::Coordinate((*it)(0), (*it)(1)));
      pointcloud.insertPoint(*it);
    }
  }
  centerDisplayOnLV03(path[0](0), path[0](1), true);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Path2DTab::centerDisplayOnWGS84(double latitude, double longitude,
    bool pos) {
  double east, north, height;
  Utils::WGS84ToLV03(latitude, longitude, 0, east, north, height);
  centerDisplayOnLV03(east, north, pos);
}

void Path2DTab::centerDisplayOnLV03(double east, double north, bool pos) {
  mLastCenterEast = east;
  mLastCenterNorth = north;
  const auto mapResolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  MapGrid subMap(
    MapGrid::Coordinate(east - 1.5 * mapResolution(0),
    north - 1.5 * mapResolution(1)),
    MapGrid::Coordinate(east + 1.5 * mapResolution(0),
    north + 1.5 * mapResolution(1)),
    mapResolution);
  if (subMap.getNumCells() != MapGrid::Index(3, 3)) {
    std::cerr << "wrong submap" << std::endl;
    return;
  }
  for (size_t j = 0; j < mPathDisplay.size(); ++j) {
    View2d::getInstance().getScene().removeItem(mPathDisplay[j]);
    delete mPathDisplay[j];
  }
  mPathDisplay.clear();
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mSymMapDisplay.getNumCells(); mSymMapDisplay.incrementIndex(i)) {
    if (mSymMapDisplay[i]) {
      View2d::getInstance().getScene().removeItem(mSymMapDisplay[i]);
      delete mSymMapDisplay[i];
      mSymMapDisplay[i] = 0;
    }
    if (mAerialMapDisplay[i]) {
      View2d::getInstance().getScene().removeItem(mAerialMapDisplay[i]);
      delete mAerialMapDisplay[i];
      mAerialMapDisplay[i] = 0;
    }
    if (mInfoMapDisplay[i]) {
      View2d::getInstance().getScene().removeItem(mInfoMapDisplay[i]);
      delete mInfoMapDisplay[i];
      mInfoMapDisplay[i] = 0;
    }
    try {
      const auto index = mMapGrids[mUi->zoomSlider->sliderPosition()].
        getIndex(subMap.getCoordinates(i));
      const auto coordinate = mMapGrids[mUi->zoomSlider->sliderPosition()].
        getCoordinates(index);
      std::string symMapFileName = mUi->folderEdit->text().toStdString() + "/" +
        Tools::downloadMapTile(coordinate(0), coordinate(1),
          Tools::zoomLevels[mUi->zoomSlider->sliderPosition()],
          mUi->folderEdit->text().toStdString(), Tools::pixelWidth,
          Tools::pixelHeight, Tools::MapType::symbolic,
          Tools::MapFormat::png);
      QImage symMapimage(symMapFileName.c_str());
      if (symMapimage.isNull()) {
        std::cerr << "Cannot load " << symMapFileName << std::endl;
      }
      else {
        mSymMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(symMapimage));
        mSymMapDisplay[i]->setPos(mSymMapDisplay.getCoordinates(i)(0) -
          Tools::pixelWidth / 2,
          3 * Tools::pixelHeight - mSymMapDisplay.getCoordinates(i)(1) -
          Tools::pixelHeight / 2);
        mSymMapDisplay[i]->setVisible(mUi->symbolicRadioButton->isChecked());
        mSymMapDisplay[i]->setZValue(0.7);
      }
      std::string aerialMapFileName =
        mUi->folderEdit->text().toStdString() + "/" +
        Tools::downloadMapTile(coordinate(0), coordinate(1),
          Tools::zoomLevels[mUi->zoomSlider->sliderPosition()],
          mUi->folderEdit->text().toStdString(), Tools::pixelWidth,
          Tools::pixelHeight, Tools::MapType::aerial,
          Tools::MapFormat::png);
      QImage aerialMapimage(aerialMapFileName.c_str());
      if (aerialMapimage.isNull()) {
        std::cerr << "Cannot load " << aerialMapFileName << std::endl;
      }
      else {
        mAerialMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(aerialMapimage));
        mAerialMapDisplay[i]->setPos(mAerialMapDisplay.getCoordinates(i)(0) -
          Tools::pixelWidth / 2,
          3 * Tools::pixelHeight - mAerialMapDisplay.getCoordinates(i)(1) -
          Tools::pixelHeight / 2);
        mAerialMapDisplay[i]->setVisible(mUi->aerialRadioButton->isChecked());
        mAerialMapDisplay[i]->setZValue(0.7);
      }
      std::string infoMapFileName = 
        mUi->folderEdit->text().toStdString() + "/" +
        Tools::downloadMapTile(coordinate(0), coordinate(1),
          Tools::zoomLevels[mUi->zoomSlider->sliderPosition()],
          mUi->folderEdit->text().toStdString(), Tools::pixelWidth,
          Tools::pixelHeight, Tools::MapType::info,
          Tools::MapFormat::png);
      QImage infoMapimage(infoMapFileName.c_str());
      if (infoMapimage.isNull()) {
        std::cerr << "Cannot load " << infoMapFileName << std::endl;
      }
      else {
        mInfoMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(infoMapimage));
        mInfoMapDisplay[i]->setPos(mInfoMapDisplay.getCoordinates(i)(0) -
          Tools::pixelWidth / 2,
          3 * Tools::pixelHeight - mInfoMapDisplay.getCoordinates(i)(1) -
          Tools::pixelHeight / 2);
        mInfoMapDisplay[i]->setVisible(mUi->infoCheckBox->isChecked());
        mInfoMapDisplay[i]->setZValue(0.8);
      }
      const auto pointcloud =
        mMapGrids[mUi->zoomSlider->sliderPosition()].getCell(index);
      for (auto it = pointcloud.getPointBegin(); it != pointcloud.getPointEnd();
          ++it) {
        const auto minIndex = mMapGrids[mUi->zoomSlider->sliderPosition()].
          getIndex(subMap.getCoordinates(MapGrid::Index(0, 0)));
        const auto minCoordinate = mMapGrids[mUi->zoomSlider->sliderPosition()].
          getCoordinates(minIndex) -
        mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution() / 2;
        const auto position = (MapGrid::Coordinate((*it)(0), (*it)(1)) -
          minCoordinate) / Tools::zoomLevels[mUi->zoomSlider->sliderPosition()];
        const double pixelX = position(0);
        const double pixelY = 3 * Tools::pixelHeight - position(1);
        QGraphicsItem* ellipse =
          View2d::getInstance().getScene().addEllipse(pixelX, pixelY, 1, 1,
          QPen(Qt::red));
        ellipse->setZValue(1.0);
        mPathDisplay.push_back(ellipse);
      }
    }
    catch (...) {
      continue;
    }
  }
  if (pos) {
    mLastPosEast = east;
    mLastPosNorth = north;
  }
}

void Path2DTab::mapBrowseClicked() {
  QString directory = QFileDialog::getExistingDirectory(this, "Open Directory",
    mUi->folderEdit->text(), QFileDialog::ShowDirsOnly |
    QFileDialog::DontResolveSymlinks);
  setMapFolder(directory);
}

void Path2DTab::aerialToggled(bool checked) {
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mSymMapDisplay.getNumCells();
      mSymMapDisplay.incrementIndex(i)) {
    if (mSymMapDisplay[i])
      mSymMapDisplay[i]->setVisible(mUi->symbolicRadioButton->isChecked());
    if (mAerialMapDisplay[i])
      mAerialMapDisplay[i]->setVisible(mUi->aerialRadioButton->isChecked());
  }
}

void Path2DTab::infoToggled(bool checked) {
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mInfoMapDisplay.getNumCells(); mInfoMapDisplay.incrementIndex(i)) {
    if (mInfoMapDisplay[i])
      mInfoMapDisplay[i]->setVisible(mUi->infoCheckBox->isChecked());
  }
}

void Path2DTab::zoomChanged(int value) {
  centerDisplayOnLV03(mLastCenterEast, mLastCenterNorth, false);
}

void Path2DTab::leftClicked() {
  auto resolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  centerDisplayOnLV03(mLastCenterEast - resolution(0), mLastCenterNorth, false);
}

void Path2DTab::rightClicked() {
  auto resolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  centerDisplayOnLV03(mLastCenterEast + resolution(0), mLastCenterNorth, false);
}

void Path2DTab::upClicked() {
  auto resolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  centerDisplayOnLV03(mLastCenterEast, mLastCenterNorth + resolution(1), false);
}

void Path2DTab::downClicked() {
  auto resolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  centerDisplayOnLV03(mLastCenterEast, mLastCenterNorth - resolution(1), false);
}
