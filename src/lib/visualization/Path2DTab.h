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

/** \file Path2DTab.h
    \brief This file defines the Path2DTab class which is the control for
           displaying a map
  */

#ifndef PATH2DTAB_H
#define PATH2DTAB_H

#include <string>
#include <vector>
#include <array>

#include <QtCore/QString>
#include <QtGui/QGraphicsItem>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "data-structures/Grid.h"

class Ui_Path2DTab;

/** The Path2DTab class is the control for the map displaying
    \brief Map display
  */
class Path2DTab :
  public Control,
  public Singleton<Path2DTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Path2DTab(const Path2DTab& other);
  /// Assignment operator
  Path2DTab& operator = (const Path2DTab& other);
  /** @}
    */

public:
  /** \name Types definitions
    @{
    */
  /// Map grid for queries
  typedef Grid<double, char, 2> MapGrid;
  /// Display grid
  typedef Grid<double, QGraphicsItem*, 2> DisplayGrid;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Path2DTab();
  /// Destructor
  virtual ~Path2DTab();
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
  void centerDisplayOnLV03(double east, double north, bool pos = true);
  /// Center display on given WGS84 coordinates
  void centerDisplayOnWGS84(double latitude, double longitude, bool pos = true);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_Path2DTab* mUi;
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
  /// Last position east
  double mLastPosEast;
  /// Last position north
  double mLastPosNorth;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Map folder browse clicked
  void mapBrowseClicked();
  /// Aerial view toggled
  void aerialToggled(bool checked);
  /// Info view toggled
  void infoToggled(bool checked);
  /// Zoom level changed
  void zoomChanged(int value);
  /// Left clicked
  void leftClicked();
  /// Right clicked
  void rightClicked();
  /// Up clicked
  void upClicked();
  /// Down clicked
  void downClicked();
  /** @}
    */

};

#endif // PATH2DTAB_H
