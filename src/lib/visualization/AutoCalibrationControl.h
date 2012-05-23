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

/** \file AutoCalibrationControl.h
    \brief This file defines the AutoCalibrationControl class which is the
           control for auto calibration of the Applanix
  */

#ifndef AUTOCALIBRATIONCONTROL_H
#define AUTOCALIBRATIONCONTROL_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_AutoCalibrationControl;
class Message;

/** The AutoCalibrationControl class is the control for the auto calibration of
    the Applanix.
    \brief Auto calibration control
  */
class AutoCalibrationControl :
  public Control,
  public Singleton<AutoCalibrationControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  AutoCalibrationControl(const AutoCalibrationControl& other);
  /// Assignment operator
  AutoCalibrationControl& operator = (const AutoCalibrationControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  AutoCalibrationControl();
  /// Destructor
  virtual ~AutoCalibrationControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_AutoCalibrationControl* mUi;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Apply general calibration
  void applyGeneralPressed();
  /// Apply GAMS calibration
  void applyGAMSPressed();
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  void sendMessage(boost::shared_ptr<Message> msg);
  /** @}
    */

};

#endif // AUTOCALIBRATIONCONTROL_H
