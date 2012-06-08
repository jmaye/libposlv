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

#include "visualization/MapTab.h"

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

#include <QtCore/QDir>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "visualization/View2d.h"
#include "sensor/Utils.h"

#include "ui_MapTab.h"

/******************************************************************************/
/* Static initialization                                                      */
/******************************************************************************/

const std::array<double, 9> MapTab::mZoomLevels =
  {512, 128, 32, 8, 4, 2, 1, 0.5, 0.25};

const std::string MapTab::mImageFormat = "png";

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MapTab::MapTab() :
    mUi(new Ui_MapTab()) {
  mUi->setupUi(this);
  setMapFolder(QDir::current().path() + QString("/maps"));
//  std::ifstream gridFile(mapFolder + "grid_sym_"
//    "468604_60945_853898_317923_32768_32768.bin");
//  MapGrid mapTiles(MapGrid::Coordinate(468604, 60945),
//    MapGrid::Coordinate(853898, 317923),
//    MapGrid::Coordinate(32768, 32768));
//  mapTiles.readBinary(gridFile);
//  mMapGrids.push_back(mapTiles);
//  size_t pos = 0;
//  for (MapGrid::Index i = MapGrid::Index::Zero();
//      i != mapTiles.getNumCells(); mapTiles.incrementIndex(i)) {
//    QImage image(mapTiles[i].c_str());
//    QGraphicsItem* imageItem =
//      View2d::getInstance().getScene().addPixmap(QPixmap::fromImage(image));
//    imageItem->setPos(i(0) * 255.0, i(1) * -255.0);
//  }
}

MapTab::~MapTab() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MapTab::setMapFolder(const QString& folderName) {
  mUi->folderEdit->setText(folderName);
  if (!boost::filesystem::exists(folderName.toStdString() + "/map_info.txt")) {
    QMessageBox::information(this, "Maps Visualizer",
      tr("Cannot find map info file in %1.").arg(folderName));
    return;
  }
  mMapGrids.clear();
  std::ifstream mapInfoFile(folderName.toStdString() + "/map_info.txt");
  double minEast, minNorth, maxEast, maxNorth;
  mapInfoFile >> minEast >> minNorth >> maxEast >> maxNorth;
  for (size_t i = 0; i < mZoomLevels.size(); ++i)
    mMapGrids.push_back(MapGrid(MapGrid::Coordinate(minEast, minNorth),
      MapGrid::Coordinate(maxEast, maxNorth),
      MapGrid::Coordinate(mZoomLevels[i] * mPixelWidth,
      mZoomLevels[i] * mPixelHeight)));
}

void MapTab::setSliderPosition(int pos) {
  mUi->zoomSlider->setSliderPosition(pos);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MapTab::mapBrowseClicked() {
  QString directory = QFileDialog::getExistingDirectory(this, "Open Directory",
    mUi->folderEdit->text(), QFileDialog::ShowDirsOnly |
    QFileDialog::DontResolveSymlinks);
  setMapFolder(directory);
}

void MapTab::aerialToggled(bool checked) {
}

void MapTab::infoToggled(bool checked) {
}

void MapTab::zoomChanged(int value) {
}

void MapTab::updatePosition(double latitude, double longitude,
    double altitude) {
  double east, north, height;
  Utils::WGS84ToLV03(latitude, longitude, altitude, east, north, height);
  if (!mMapGrids[4].isInRange(MapGrid::Coordinate(east, north))) {
    std::cerr << "Coordinates not in range" << std::endl;
    return;
  }
  auto index = mMapGrids[5].getIndex(MapGrid::Coordinate(east, north));
  auto coordinate = mMapGrids[5].getCoordinates(index);
  std::stringstream imgFileName;
  imgFileName << mUi->folderEdit->text().toStdString() << "/";
  imgFileName << "sym" << "_" << (int)coordinate(0) << "_"
    << (int)coordinate(1) << "_" << mZoomLevels[5] << "." << mImageFormat;
  QImage image(imgFileName.str().c_str());
  if (image.isNull()) {
    std::cerr << "Cannot load " << imgFileName.str() << std::endl;
    return;
  }
  QGraphicsItem* imageItem =
    View2d::getInstance().getScene().addPixmap(QPixmap::fromImage(image));
//  imageItem->setPos(index(0) * 256, index(1) * 256);
//  View2d::getInstance().centerOn(index(0) * 256, index(1) * 256);
//  if (mGraphicsItems.find("image") != mGraphicsItems.end()) {
//    View2d::getInstance().getScene().removeItem(mGraphicsItems["image"]);
//    delete mGraphicsItems["image"];
//  }
//  mGraphicsItems["image"]= imageItem;
}

void MapTab::updateUncertainty(double latitude, double longitude,
    double altitude) {
}
