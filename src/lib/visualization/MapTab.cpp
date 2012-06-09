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
#include "com/TCPConnectionClient.h"
#include "com/HTTPProtocol.h"
#include "com/NetUtils.h"
#include "base/BinaryStreamWriter.h"
#include "base/BinaryStreamReader.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"

#include "ui_MapTab.h"

/******************************************************************************/
/* Static initialization                                                      */
/******************************************************************************/

const std::array<double, 9> MapTab::mZoomLevels =
  {512, 128, 32, 8, 4, 2, 1, 0.5, 0.25};

const std::string MapTab::mImageFormat = "png";

const std::string MapTab::mSymMap = "sym";

const std::string MapTab::mAerialMap = "bg";

const std::string MapTab::mInfoMap = "fg";

const double MapTab::mZurichEast = 683263;

const double MapTab::mZurichNorth = 248036;

const std::string MapTab::mServerHost = "map.search.ch";

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MapTab::MapTab() :
    mUi(new Ui_MapTab()),
    mCanvasDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3 * mPixelWidth, 3 * mPixelHeight),
      DisplayGrid::Coordinate(mPixelWidth, mPixelHeight)),
    mSymMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3 * mPixelWidth, 3 * mPixelHeight),
      DisplayGrid::Coordinate(mPixelWidth, mPixelHeight)),
    mAerialMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3 * mPixelWidth, 3 * mPixelHeight),
      DisplayGrid::Coordinate(mPixelWidth, mPixelHeight)),
    mInfoMapDisplay(DisplayGrid::Coordinate(0, 0),
      DisplayGrid::Coordinate(3 * mPixelWidth, 3 * mPixelHeight),
      DisplayGrid::Coordinate(mPixelWidth, mPixelHeight)),
    mPositionDisplay(0) {
  mUi->setupUi(this);
  setMapFolder(QDir::current().path() + QString("/maps"));
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mCanvasDisplay.getNumCells(); mCanvasDisplay.incrementIndex(i)) {
    const auto coordinate = mCanvasDisplay.getCoordinates(i) -
      DisplayGrid::Coordinate(mPixelWidth / 2, mPixelHeight / 2);
    mCanvasDisplay[i] = View2d::getInstance().getScene().addRect(
      coordinate(0), coordinate(1), mPixelWidth, mPixelHeight);
    std::stringstream number;
    number << "(" << i(0) << ", " << i(1) << ")";
    QGraphicsSimpleTextItem* text = 
      View2d::getInstance().getScene().addSimpleText(number.str().c_str());
    text->setPos(mCanvasDisplay.getCoordinates(i)(0),
      3 * mPixelHeight - mCanvasDisplay.getCoordinates(i)(1));
  }
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
  centerDisplayOnLV03(mZurichEast, mZurichNorth);
}

void MapTab::setSliderPosition(int pos) {
  mUi->zoomSlider->setSliderPosition(pos);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MapTab::centerDisplayOnWGS84(double latitude, double longitude) {
  double east, north, height;
  Utils::WGS84ToLV03(latitude, longitude, 0, east, north, height);
  centerDisplayOnLV03(east, north);
}

void MapTab::centerDisplayOnLV03(double east, double north) {
  mLastCenterEast = east;
  mLastCenterNorth = north;
  const auto mapResolution =
    mMapGrids[mUi->zoomSlider->sliderPosition()].getResolution();
  MapGrid subMap(
    MapGrid::Coordinate(east - 1.1 * mapResolution(0),
    north - 1.1 * mapResolution(1)),
    MapGrid::Coordinate(east + 1.1 * mapResolution(0),
    north + 1.1 * mapResolution(1)),
    mapResolution);
  if (subMap.getNumCells() != MapGrid::Index(3, 3)) {
    std::cerr << "wrong submap" << std::endl;
    return;
  }
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
      auto index = mMapGrids[mUi->zoomSlider->sliderPosition()].
        getIndex(subMap.getCoordinates(i));
      auto coordinate = mMapGrids[mUi->zoomSlider->sliderPosition()].
        getCoordinates(index);
      std::stringstream symMapFileName;
      symMapFileName << mUi->folderEdit->text().toStdString() << "/";
      symMapFileName << mSymMap << "_" << (int)coordinate(0) << "_"
        << (int)coordinate(1) << "_"
        << mZoomLevels[mUi->zoomSlider->sliderPosition()] << "."
        << mImageFormat;
      if (!boost::filesystem::exists(symMapFileName.str()))
        downloadMapTile(coordinate(0), coordinate(1), mSymMap,
          mZoomLevels[mUi->zoomSlider->sliderPosition()], mImageFormat);
      QImage symMapimage(symMapFileName.str().c_str());
      if (symMapimage.isNull()) {
        std::cerr << "Cannot load " << symMapFileName.str() << std::endl;
      }
      else {
        mSymMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(symMapimage));
        mSymMapDisplay[i]->setPos(mCanvasDisplay.getCoordinates(i)(0) -
          mPixelWidth / 2,
          3 * mPixelHeight - mCanvasDisplay.getCoordinates(i)(1) -
          mPixelHeight / 2);
        mSymMapDisplay[i]->setVisible(mUi->symbolicRadioButton->isChecked());
      }
      std::stringstream aerialMapFileName;
      aerialMapFileName << mUi->folderEdit->text().toStdString() << "/";
      aerialMapFileName << mAerialMap << "_" << (int)coordinate(0) << "_"
        << (int)coordinate(1) << "_"
        << mZoomLevels[mUi->zoomSlider->sliderPosition()] << "."
        << mImageFormat;
      if (!boost::filesystem::exists(aerialMapFileName.str()))
        downloadMapTile(coordinate(0), coordinate(1), mAerialMap,
          mZoomLevels[mUi->zoomSlider->sliderPosition()], mImageFormat);
      QImage aerialMapimage(aerialMapFileName.str().c_str());
      if (aerialMapimage.isNull()) {
        std::cerr << "Cannot load " << aerialMapFileName.str() << std::endl;
      }
      else {
        mAerialMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(aerialMapimage));
        mAerialMapDisplay[i]->setPos(mCanvasDisplay.getCoordinates(i)(0) -
          mPixelWidth / 2,
          3 * mPixelHeight - mCanvasDisplay.getCoordinates(i)(1) -
          mPixelHeight / 2);
        mAerialMapDisplay[i]->setVisible(mUi->aerialRadioButton->isChecked());
      }
      std::stringstream infoMapFileName;
      infoMapFileName << mUi->folderEdit->text().toStdString() << "/";
      infoMapFileName << mInfoMap << "_" << (int)coordinate(0) << "_"
        << (int)coordinate(1) << "_"
        << mZoomLevels[mUi->zoomSlider->sliderPosition()] << "."
        << mImageFormat;
      if (!boost::filesystem::exists(infoMapFileName.str()))
        downloadMapTile(coordinate(0), coordinate(1), mInfoMap,
          mZoomLevels[mUi->zoomSlider->sliderPosition()], mImageFormat);
      QImage infoMapimage(infoMapFileName.str().c_str());
      if (infoMapimage.isNull()) {
        std::cerr << "Cannot load " << infoMapFileName.str() << std::endl;
      }
      else {
        mInfoMapDisplay[i] =
          View2d::getInstance().getScene().addPixmap(
          QPixmap::fromImage(infoMapimage));
        mInfoMapDisplay[i]->setPos(mCanvasDisplay.getCoordinates(i)(0) -
          mPixelWidth / 2,
          3 * mPixelHeight - mCanvasDisplay.getCoordinates(i)(1) -
          mPixelHeight / 2);
        mInfoMapDisplay[i]->setVisible(mUi->infoCheckBox->isChecked());
      }
      if (subMap.isInRange(MapGrid::Coordinate(east, north))) {
        if (mPositionDisplay) {
          View2d::getInstance().getScene().removeItem(mPositionDisplay);
          delete mPositionDisplay;
        }
//        std::cout << subMap.getMinimum() << std::endl << std::endl;
//        std::cout << MapGrid::Coordinate(east, north) << std::endl << std::endl;
//        auto position = (MapGrid::Coordinate(east, north) - subMap.getMinimum()) /
//          mZoomLevels[mUi->zoomSlider->sliderPosition()];
//        std::cout << position << std::endl << std::endl;
        mPositionDisplay =
          View2d::getInstance().getScene().addEllipse(
          mCanvasDisplay.getCoordinates(i)(0),
          3 * mPixelHeight - mCanvasDisplay.getCoordinates(i)(1),
          10, 10, QPen(Qt::red));
      }
    }
    catch (...) {
      continue;
    }
  }
}

void MapTab::mapBrowseClicked() {
  QString directory = QFileDialog::getExistingDirectory(this, "Open Directory",
    mUi->folderEdit->text(), QFileDialog::ShowDirsOnly |
    QFileDialog::DontResolveSymlinks);
  setMapFolder(directory);
}

void MapTab::aerialToggled(bool checked) {
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mSymMapDisplay.getNumCells();
      mSymMapDisplay.incrementIndex(i)) {
    if (mSymMapDisplay[i])
      mSymMapDisplay[i]->setVisible(mUi->symbolicRadioButton->isChecked());
    if (mAerialMapDisplay[i])
      mAerialMapDisplay[i]->setVisible(mUi->aerialRadioButton->isChecked());
  }
}

void MapTab::infoToggled(bool checked) {
  for (DisplayGrid::Index i = DisplayGrid::Index::Zero();
      i != mInfoMapDisplay.getNumCells(); mInfoMapDisplay.incrementIndex(i)) {
    if (mInfoMapDisplay[i])
      mInfoMapDisplay[i]->setVisible(mUi->infoCheckBox->isChecked());
  }
}

void MapTab::zoomChanged(int value) {
  centerDisplayOnLV03(mLastCenterEast, mLastCenterNorth);
}

void MapTab::updatePosition(double latitude, double longitude,
    double altitude) {
//  centerDisplayOnWGS84(latitude, longitude);
}

void MapTab::updateUncertainty(double latitude, double longitude,
    double altitude) {
}

bool MapTab::downloadMapTile(double east, double north, const std::string&
    mapType, double zoomLevel, const std::string& format) {
  std::stringstream imgFileName;
  imgFileName << mapType << "_" << (int)east << "_" << (int)north << "_"
    << zoomLevel << "." << format;
  if (boost::filesystem::exists(mUi->folderEdit->text().toStdString() +
        imgFileName.str()))
    return false;
  std::stringstream uri;
  uri << "/chmap.en." << format << "?x=0m&y=0m&w=" << mPixelWidth << "&h="
    << mPixelHeight << "&base=" << east << "," << north << "&layer=" << mapType
    << "&zd=" << zoomLevel<< "&n=0";
  std::string httpRequest;
  httpRequest += HTTPProtocol::writeRequestLine(HTTPProtocol::Method::GET,
    uri.str());
  httpRequest += HTTPProtocol::writeGeneralHeaderLine(
    HTTPProtocol::GeneralHeader::Connection, "close");
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::Host, mServerHost);
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::UserAgent, "swissMap");
  httpRequest += "\r\n";
  try {
    TCPConnectionClient com(NetUtils::getHostIP(mServerHost), 80);
    BinaryStreamReader<TCPConnectionClient> tcpStreamReader(com);
    BinaryStreamWriter<TCPConnectionClient> tcpStreamWriter(com);
    com.open();
    tcpStreamWriter << httpRequest;
    std::string responseStatusLine =
      HTTPProtocol::readLine(tcpStreamReader);
    std::string protocol, statusCode, reasonPhrase;
    HTTPProtocol::readResponseStatusLine(responseStatusLine, protocol,
      statusCode, reasonPhrase);
    if (statusCode != "200") {
      std::cerr
        << "status code: " + statusCode + "\nreason: " + reasonPhrase
        << std::endl;
      return false;
    }
    bool chunked = false;
    size_t bytesToRead = 0;
    while (1) {
      std::string responseHeaderLine =
        HTTPProtocol::readLine(tcpStreamReader);
      if (responseHeaderLine == "\r\n")
        break;
      std::string header;
      std::string value;
      HTTPProtocol::readHeaderLine(responseHeaderLine, header, value);
      if (header ==
          HTTPProtocol::entityHeaders[
          HTTPProtocol::EntityHeader::ContentType]
          &&
          value.compare(0, 8, "image/" + format, 0, 8)) {
        std::cerr << "wrong image format returned" << std::endl;
        return false;
      }
      if (header ==
          HTTPProtocol::generalHeaders[
          HTTPProtocol::GeneralHeader::TransferEncoding] &&
          !value.compare(0, 6, "chunked", 0, 6))
        chunked = true;
      if (header ==
          HTTPProtocol::entityHeaders[
          HTTPProtocol::EntityHeader::ContentLength])
        bytesToRead = atoi(value.c_str());
    }
    std::string image;
    if (chunked)
      while (1) {
        std::string chunk = HTTPProtocol::readDataChunk(tcpStreamReader);
        if (chunk.empty())
          break;
        image.append(chunk);
      }
    else {
      char buffer[bytesToRead];
      tcpStreamReader.read(buffer, bytesToRead);
      image.assign(buffer, bytesToRead);
    }
    std::ofstream imageFile(mUi->folderEdit->text().toStdString() + "/" +
      imgFileName.str());
    imageFile.write(image.c_str(), image.size());
    imageFile.close();
    com.close();
    return true;
  }
  catch (IOException& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  catch (SystemException& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
}
