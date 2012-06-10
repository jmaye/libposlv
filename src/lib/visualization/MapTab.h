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

/** \file MapTab.h
    \brief This file defines the MapTab class which is the control for
           displaying a map
  */

#ifndef MAPTAB_H
#define MAPTAB_H

#include <string>
#include <vector>
#include <array>

#include <QtCore/QString>
#include <QtGui/QGraphicsItem>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "data-structures/Grid.h"

class Ui_MapTab;

/** The MapTab class is the control for the map displaying
    \brief Map display
  */
class MapTab :
  public Control,
  public Singleton<MapTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MapTab(const MapTab& other);
  /// Assignment operator
  MapTab& operator = (const MapTab& other);
  /** @}
    */

public:
  /** \name Types definitions
    @{
    */
  /// Map grid for queries
  typedef Grid<double, int, 2> MapGrid;
  /// Display grid
  typedef Grid<double, QGraphicsItem*, 2> DisplayGrid;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MapTab();
  /// Destructor
  virtual ~MapTab();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the map folder
  void setMapFolder(const QString& folderName);
  /// Sets the slider position
  void setSliderPosition(int pos);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Center display on given LV03 coordinates
  void centerDisplayOnLV03(double east, double north);
  /// Center display on given WGS84 coordinates
  void centerDisplayOnWGS84(double latitude, double longitude);
  /// Download map tile
  bool downloadMapTile(double east, double north, const std::string& mapType,
    double zoomLevel, const std::string& format);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_MapTab* mUi;
  /// Map grids structures for each zoom level
  std::vector<MapGrid> mMapGrids;
  /// Canvas display
  DisplayGrid mCanvasDisplay;
  /// Symbolic map display
  DisplayGrid mSymMapDisplay;
  /// Aerial map display
  DisplayGrid mAerialMapDisplay;
  /// Info map display
  DisplayGrid mInfoMapDisplay;
  /// Position
  QGraphicsItem* mPositionDisplay;
  /// Last center east
  double mLastCenterEast;
  /// Last center north
  double mLastCenterNorth;
  /// Last uncertainty east
  double mLastUncertaintyEast;
  /// Last uncertainty north
  double mLastUncertaintyNorth;
  /// Zoom levels
  static const std::array<double, 9> mZoomLevels; 
  /// Pixel width
  static const int mPixelWidth = 256;
  /// Pixel height
  static const int mPixelHeight = 256;
  /// Image format
  static const std::string mImageFormat;
  /// Symbolic map query
  static const std::string mSymMap;
  /// Aerial map query
  static const std::string mAerialMap;
  /// Info map query
  static const std::string mInfoMap;
  /// Zurich east
  static const double mZurichEast;
  /// Zurich north
  static const double mZurichNorth;
  /// Server host from swissmap
  static const std::string mServerHost;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Update position
  void updatePosition(double latitude, double longitude, double altitude);
  /// Update uncertainty
  void updateUncertainty(double latitude, double longitude, double altitude);
  /// Map folder browse clicked
  void mapBrowseClicked();
  /// Aerial view toggled
  void aerialToggled(bool checked);
  /// Info view toggled
  void infoToggled(bool checked);
  /// Zoom level changed
  void zoomChanged(int value);
  /** @}
    */

};

#endif // MAPTAB_H
