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
    \brief This file defines the MapTab class which is the
           control for displaying a map
  */

#ifndef MAPTAB_H
#define MAPTAB_H

#include <QtCore/QTimer>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_MapTab;
class Packet;

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

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_MapTab* mUi;
  /// Refresh timer
  QTimer mTimer;
  /// Last latitude observed
  double mLatitude;
  /// Last longitude observed
  double mLongitude;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(boost::shared_ptr<Packet> packet);
  /// Timer timeout
  void timerTimeout();
  /** @}
    */

};

#endif // MAPTAB_H
