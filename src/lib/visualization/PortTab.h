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

/** \file PortTab.h
    \brief This file defines the PortTab class which is the control
           for the ports
  */

#ifndef PORTTAB_H
#define PORTTAB_H

#include <map>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_PortTab;
class Packet;

/** The PortTab class is the control for the time of the Applanix.
    \brief Time control
  */
class PortTab :
  public Control,
  public Singleton<PortTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PortTab(const PortTab& other);
  /// Assignment operator
  PortTab& operator = (const PortTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  PortTab();
  /// Destructor
  virtual ~PortTab();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_PortTab* mUi;
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

#endif // PORTTAB_H
