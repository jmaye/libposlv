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

/** \file NavigationModeControlTab.h
    \brief This file defines the NavigationModeControlTab class which is the
           control of navigation mode.
  */

#ifndef NAVIGATIONMODECONTROLTAB_H
#define NAVIGATIONMODECONTROLTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_NavigationModeControlTab;
class Packet;

/** The NavigationModeControlTab class is the control for the navigation mode of
    the Applanix.
    \brief Navigation mode control
  */
class NavigationModeControlTab :
  public Control,
  public Singleton<NavigationModeControlTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  NavigationModeControlTab(const NavigationModeControlTab& other);
  /// Assignment operator
  NavigationModeControlTab& operator = (const NavigationModeControlTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  NavigationModeControlTab();
  /// Destructor
  virtual ~NavigationModeControlTab();
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
  Ui_NavigationModeControlTab* mUi;
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

#endif // NAVIGATIONMODECONTROLTAB_H
