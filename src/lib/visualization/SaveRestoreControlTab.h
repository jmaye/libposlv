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

/** \file SaveRestoreControlTab.h
    \brief This file defines the SaveRestoreControlTab class which is the
           control for the save/restore function
  */

#ifndef SAVERESTORECONTROLTAB_H
#define SAVERESTORECONTROLTAB_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_SaveRestoreControlTab;
class Packet;

/** The SaveRestoreControlTab class is the control for the save/restore function
    of the Applanix.
    \brief Save/Restore control
  */
class SaveRestoreControlTab :
  public Control,
  public Singleton<SaveRestoreControlTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  SaveRestoreControlTab(const SaveRestoreControlTab& other);
  /// Assignment operator
  SaveRestoreControlTab& operator = (const SaveRestoreControlTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  SaveRestoreControlTab();
  /// Destructor
  virtual ~SaveRestoreControlTab();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_SaveRestoreControlTab* mUi;
  /// Specifies if the tab is in control mode
  bool mControlMode;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
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
  void writePacket(boost::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // SAVERESTORECONTROLTAB_H
