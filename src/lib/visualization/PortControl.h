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

/** \file PortControl.h
    \brief This file defines the PortControl class which is the control
           for the time
  */

#ifndef PORTCONTROL_H
#define PORTCONTROL_H

#include <map>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_PortControl;
class Packet;

/** The PortControl class is the control for the time of the Applanix.
    \brief Time control
  */
class PortControl :
  public Control,
  public Singleton<PortControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PortControl(const PortControl& other);
  /// Assignment operator
  PortControl& operator = (const PortControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  PortControl();
  /// Destructor
  virtual ~PortControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_PortControl* mUi;
  /// Mapping for baudrate
  std::map<uint8_t, uint32_t> mBaudrateMap;
  /// Mapping for parity
  std::map<uint8_t, std::string> mParityMap;
  /// Mapping for stop bits
  std::map<uint8_t, std::string> mStopMap;
  /// Mapping for flow control
  std::map<uint8_t, std::string> mFlowMap;
  /// Mapping for input select
  std::map<uint16_t, std::string> mInputMap;
  /// Mapping for output select
  std::map<uint16_t, std::string> mOutputMap;
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

#endif // PORTCONTROL_H
