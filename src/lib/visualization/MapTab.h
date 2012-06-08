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
#include <map>
#include <vector>
#include <array>

#include <QtCore/QString>
#include <QtGui/QGraphicsItem>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "data-structures/MapGrid.h"

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

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_MapTab* mUi;
  /// Graphic items associated with this control
  std::map<std::string, QGraphicsItem*> mGraphicsItems;
  /// Map grids structures for each zoom level
  std::vector<MapGrid> mMapGrids;
  /// Zoom levels
  static const std::array<double, 9> mZoomLevels;
  /// Pixel width
  static const int mPixelWidth = 256;
  /// Pixel height
  static const int mPixelHeight = 256;
  /// Image format
  static const std::string mImageFormat;
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
