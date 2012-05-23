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

/** \file StatusControl.h
    \brief This file defines the StatusControl class which is the control
           for the status
  */

#ifndef STATUSCONTROL_H
#define STATUSCONTROL_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_StatusControl;
class Packet;

/** The StatusControl class is the control for the status of the Applanix.
    \brief Status control
  */
class StatusControl :
  public Control,
  public Singleton<StatusControl> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  StatusControl();
  /// Destructor
  virtual ~StatusControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_StatusControl* mUi;
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

#endif // STATUSCONTROL_H
