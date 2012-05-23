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

/** \file GAMSControl.h
    \brief This file defines the GAMSControl class which is the control
           for the GAMS solution
  */

#ifndef GAMSCONTROL_H
#define GAMSCONTROL_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_GAMSControl;
class Packet;

/** The GAMSControl class is the control for the GAMS solution of the Applanix.
    \brief GAMS solution control
  */
class GAMSControl :
  public Control,
  public Singleton<GAMSControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GAMSControl(const GAMSControl& other);
  /// Assignment operator
  GAMSControl& operator = (const GAMSControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  GAMSControl();
  /// Destructor
  virtual ~GAMSControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_GAMSControl* mUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
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

#endif // GAMSCONTROL_H
