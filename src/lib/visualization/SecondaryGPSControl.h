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

/** \file SecondaryGPSControl.h
    \brief This file defines the SecondaryGPSControl class which is the control
           for the secondary GPS
  */

#ifndef SECONDARYGPSCONTROL_H
#define SECONDARYGPSCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_SecondaryGPSControl;

/** The SecondaryGPSControl class is the control for the secondary GPS of the
    Applanix.
    \brief Secondary GPS control
  */
class SecondaryGPSControl :
  public Control,
  public Singleton<SecondaryGPSControl> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  SecondaryGPSControl();
  /// Destructor
  virtual ~SecondaryGPSControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_SecondaryGPSControl* mpUi;
  /** @}
    */

};

#endif // SECONDARYGPSCONTROL_H
