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

/** \file Aux1GPSControl.h
    \brief This file defines the Aux1GPSControl class which is the control for
           the auxiliary 1 GPS
  */

#ifndef AUX1GPSCONTROL_H
#define AUX1GPSCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_Aux1GPSControl;

/** The Aux1GPSControl class is the control for the auxiliary 1 GPS of the
    Applanix.
    \brief Auxiliary 1 GPS control
  */
class Aux1GPSControl :
  public Control,
  public Singleton<Aux1GPSControl> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Aux1GPSControl();
  /// Destructor
  virtual ~Aux1GPSControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_Aux1GPSControl* mpUi;
  /** @}
    */

};

#endif // AUX1GPSCONTROL_H
