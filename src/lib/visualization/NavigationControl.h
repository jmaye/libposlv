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

/** \file NavigationControl.h
    \brief This file defines the NavigationControl class which is the control
           for the navigation
  */

#ifndef NAVIGATIONCONTROL_H
#define NAVIGATIONCONTROL_H

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "types/Packet.h"

class Ui_NavigationControl;
class Group;

/** The NavigationControl class is the control for the navigation of the
    Applanix.
    \brief Navigation control
  */
class NavigationControl :
  public Control,
  public Singleton<NavigationControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  NavigationControl(const NavigationControl& other);
  /// Assignment operator
  NavigationControl& operator = (const NavigationControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  NavigationControl();
  /// Destructor
  virtual ~NavigationControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_NavigationControl* mUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void packetRead(boost::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // NAVIGATIONCONTROL_H
