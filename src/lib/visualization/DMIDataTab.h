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

/** \file DMIDataTab.h
    \brief This file defines the DMIDataTab class which is the control
           for the DMI
  */

#ifndef DMIDATATAB_H
#define DMIDATATAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_DMIDataTab;
class Packet;

/** The DMIDataTab class is the control for the DMI of the Applanix.
    \brief DMI control
  */
class DMIDataTab :
  public Control,
  public Singleton<DMIDataTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DMIDataTab(const DMIDataTab& other);
  /// Assignment operator
  DMIDataTab& operator = (const DMIDataTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DMIDataTab();
  /// Destructor
  virtual ~DMIDataTab();
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
  Ui_DMIDataTab* mUi;
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
  void readPacket(std::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // DMIDATATAB_H
