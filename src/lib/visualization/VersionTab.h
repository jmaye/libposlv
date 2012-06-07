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

/** \file VersionTab.h
    \brief This file defines the VersionTab class which is the control
           for the version
  */

#ifndef VERSIONTAB_H
#define VERSIONTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_VersionTab;
class Packet;

/** The VersionTab class is the control for the version of the Applanix.
    \brief Version control
  */
class VersionTab :
  public Control,
  public Singleton<VersionTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  VersionTab(const VersionTab& other);
  /// Assignment operator
  VersionTab& operator = (const VersionTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  VersionTab();
  /// Destructor
  virtual ~VersionTab();
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
  Ui_VersionTab* mUi;
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

#endif // VERSIONTAB_H
