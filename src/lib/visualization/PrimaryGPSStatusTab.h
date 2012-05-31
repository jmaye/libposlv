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

/** \file PrimaryGPSStatusTab.h
    \brief This file defines the PrimaryGPSStatusTab class which is the control
           for the primary GPS
  */

#ifndef PRIMARYGPSSTATUSTAB_H
#define PRIMARYGPSSTATUSTAB_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_PrimaryGPSStatusTab;
class Packet;

/** The PrimaryGPSStatusTab class is the control for the primary GPS of the
    Applanix.
    \brief Primary GPS control
  */
class PrimaryGPSStatusTab :
  public Control,
  public Singleton<PrimaryGPSStatusTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PrimaryGPSStatusTab(const PrimaryGPSStatusTab& other);
  /// Assignment operator
  PrimaryGPSStatusTab& operator = (const PrimaryGPSStatusTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  PrimaryGPSStatusTab();
  /// Destructor
  virtual ~PrimaryGPSStatusTab();
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
  Ui_PrimaryGPSStatusTab* mUi;
  /// Mapping for the status messages
  std::map<int8_t, std::string> mStatusMsg;
  /// Mapping for the GPS type messages
  std::map<uint16_t, std::string> mGPSTypeMsg;
  /// Mapping for time sync. messages
  std::map<uint8_t, std::string> mTimeSyncMsg;
  /// Mapping for channel status
  std::map<uint16_t, std::string> mChannelStatusMsg;
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

#endif // PRIMARYGPSSTATUSTAB_H
