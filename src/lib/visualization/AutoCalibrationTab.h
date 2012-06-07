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

/** \file AutoCalibrationTab.h
    \brief This file defines the AutoCalibrationTab class which is the
           control for auto calibration of the Applanix
  */

#ifndef AUTOCALIBRATIONTAB_H
#define AUTOCALIBRATIONTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_AutoCalibrationTab;
class Packet;

/** The AutoCalibrationTab class is the control for the auto calibration of
    the Applanix.
    \brief Auto calibration control
  */
class AutoCalibrationTab :
  public Control,
  public Singleton<AutoCalibrationTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  AutoCalibrationTab(const AutoCalibrationTab& other);
  /// Assignment operator
  AutoCalibrationTab& operator = (const AutoCalibrationTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  AutoCalibrationTab();
  /// Destructor
  virtual ~AutoCalibrationTab();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_AutoCalibrationTab* mUi;
  /// Specifies if the tab is in control mode
  bool mControlMode;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(std::shared_ptr<Packet> packet);
  /// Apply general calibration
  void applyGeneralPressed();
  /// Apply GAMS calibration
  void applyGAMSPressed();
  /// Device connected
  void deviceConnected(bool connected);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  void writePacket(std::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // AUTOCALIBRATIONTAB_H
