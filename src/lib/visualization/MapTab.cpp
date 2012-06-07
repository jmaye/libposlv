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

#include "visualization/View2d.h"
#include "sensor/Utils.h"

#include "ui_MapTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MapTab::MapTab(const std::string& mapFolder) :
    mUi(new Ui_MapTab()),
    mMapFolder(mapFolder) {
  mUi->setupUi(this);
  std::ifstream gridFile(mapFolder + "grid_sym_"
    "468604_60945_853898_317923_32768_32768.bin");
  MapGrid mapTiles(MapGrid::Coordinate(468604, 60945),
    MapGrid::Coordinate(853898, 317923),
    MapGrid::Coordinate(32768, 32768));
  mapTiles.readBinary(gridFile);
  mMapGrids.push_back(mapTiles);
  size_t pos = 0;
  for (MapGrid::Index i = MapGrid::Index::Zero();
      i != mapTiles.getNumCells(); mapTiles.incrementIndex(i)) {
    QImage image(mapTiles[i].c_str());
    QGraphicsItem* imageItem =
      View2d::getInstance().getScene().addPixmap(QPixmap::fromImage(image));
    imageItem->setPos(i(0) * 256.0, i(1) * -256.0);
  }
}

MapTab::~MapTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MapTab::updatePosition(double latitude, double longitude,
    double altitude) {
  double east, north, height;
//  Utils::WGS84ToLV03(latitude, longitude, altitude, east, north, height);
//  std::string fileName = mMapFolder +
//    mMapGrids[0](MapGrid::Coordinate(east, north));
//  MapGrid::Index index =
//    mMapGrids[0].getIndex(MapGrid::Coordinate(east, north));
//  QImage image(fileName.c_str());
//  QGraphicsItem* imageItem =
//    View2d::getInstance().getScene().addPixmap(QPixmap::fromImage(image));
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
