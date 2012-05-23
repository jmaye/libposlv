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

/** \file CalibrationControl.h
    \brief This file defines the CalibrationControl class which is the control
           for the calibration
  */

#ifndef CALIBRATIONCONTROL_H
#define CALIBRATIONCONTROL_H

#include "boost/shared_ptr.hpp"

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_CalibrationControl;
class Packet;

/** The CalibrationControl class is the control for the calibration of the
    Applanix.
    \brief Calibration control
  */
class CalibrationControl :
  public Control,
  public Singleton<CalibrationControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  CalibrationControl(const CalibrationControl& other);
  /// Assignment operator
  CalibrationControl& operator = (const CalibrationControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  CalibrationControl();
  /// Destructor
  virtual ~CalibrationControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_CalibrationControl* mUi;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void packetRead(boost::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // CALIBRATIONCONTROL_H
