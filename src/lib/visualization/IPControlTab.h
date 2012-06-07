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

/** \file IPControlTab.h
    \brief This file defines the IPControlTab class which is the control
           for the IP of the device.
  */

#ifndef IPCONTROLTAB_H
#define IPCONTROLTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_IPControlTab;
class Packet;

/** The IPControlTab class is the control for the IP address of the Applanix.
    \brief IP address control
  */
class IPControlTab :
  public Control,
  public Singleton<IPControlTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  IPControlTab(const IPControlTab& other);
  /// Assignment operator
  IPControlTab& operator = (const IPControlTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  IPControlTab();
  /// Destructor
  virtual ~IPControlTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields(bool enable);
  /// Sets readonly fields
  void setReadOnlyFields(bool readonly);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_IPControlTab* mUi;
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
  /// Apply pressed
  void applyPressed();
  /// Device connected
  void deviceConnected(bool connected);
  /** @}
    */

signals:
  /** \name Signals
    @{
    */
  /// Sends a packet to the POS
  void writePacket(std::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // IPCONTROLTAB_H
