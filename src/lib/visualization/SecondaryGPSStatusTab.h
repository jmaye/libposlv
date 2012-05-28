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

/** \file SecondaryGPSStatusTab.h
    \brief This file defines the SecondaryGPSStatusTab class which is the
           control for the secondary GPS
  */

#ifndef SECONDARYGPSSTATUSTAB_H
#define SECONDARYGPSSTATUSTAB_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_SecondaryGPSStatusTab;
class Packet;

/** The SecondaryGPSStatusTab class is the control for the secondary GPS of the
    Applanix.
    \brief Secondary GPS control
  */
class SecondaryGPSStatusTab :
  public Control,
  public Singleton<SecondaryGPSStatusTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  SecondaryGPSStatusTab(const SecondaryGPSStatusTab& other);
  /// Assignment operator
  SecondaryGPSStatusTab& operator = (const SecondaryGPSStatusTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  SecondaryGPSStatusTab();
  /// Destructor
  virtual ~SecondaryGPSStatusTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields();
  /// Disable the fields
  void disableFields();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_SecondaryGPSStatusTab* mUi;
  /// Mapping for the status messages
  std::map<int8_t, std::string> mStatusMsg;
  /// Mapping for the GPS type messages
  std::map<uint16_t, std::string> mGPSTypeMsg;
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

#endif // SECONDARYGPSSTATUSTAB_H
