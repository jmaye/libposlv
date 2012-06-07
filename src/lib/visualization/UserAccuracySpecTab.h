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

/** \file UserAccuracySpecTab.h
    \brief This file defines the UserAccuracySpecTab class which is the control
           for the user accuracy specification
  */

#ifndef USERACCURACYSPECTAB_H
#define USERACCURACYSPECTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_UserAccuracySpecTab;
class Packet;

/** The UserAccuracySpecTab class is the control for the user accuracy
    specification of the Applanix.
    \brief User accuracy specification control
  */
class UserAccuracySpecTab :
  public Control,
  public Singleton<UserAccuracySpecTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  UserAccuracySpecTab(const UserAccuracySpecTab& other);
  /// Assignment operator
  UserAccuracySpecTab& operator = (const UserAccuracySpecTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  UserAccuracySpecTab();
  /// Destructor
  virtual ~UserAccuracySpecTab();
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
  Ui_UserAccuracySpecTab* mUi;
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

#endif // USERACCURACYSPECTAB_H
