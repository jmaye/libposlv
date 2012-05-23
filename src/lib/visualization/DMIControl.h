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

/** \file DMIControl.h
    \brief This file defines the DMIControl class which is the control
           for the DMI
  */

#ifndef DMICONTROL_H
#define DMICONTROL_H

#include "boost/shared_ptr.hpp"

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_DMIControl;
class Packet;

/** The DMIControl class is the control for the DMI of the Applanix.
    \brief DMI control
  */
class DMIControl :
  public Control,
  public Singleton<DMIControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DMIControl(const DMIControl& other);
  /// Assignment operator
  DMIControl& operator = (const DMIControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DMIControl();
  /// Destructor
  virtual ~DMIControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_DMIControl* mUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
  /// Mapping for the type messages
  std::map<uint8_t, std::string> mTypeMsg;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(boost::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // DMICONTROL_H
