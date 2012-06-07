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

/** \file IMUDataTab.h
    \brief This file defines the IMUDataTab class which is the control
           for the IMU
  */

#ifndef IMUDATATAB_H
#define IMUDATATAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_IMUDataTab;
class Packet;

/** The IMUDataTab class is the control for the IMU of the Applanix.
    \brief IMU control
  */
class IMUDataTab :
  public Control,
  public Singleton<IMUDataTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  IMUDataTab(const IMUDataTab& other);
  /// Assignment operator
  IMUDataTab& operator = (const IMUDataTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  IMUDataTab();
  /// Destructor
  virtual ~IMUDataTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields(bool enable);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_IMUDataTab* mUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(std::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // IMUDATATAB_H
