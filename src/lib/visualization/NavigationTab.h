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

/** \file NavigationTab.h
    \brief This file defines the NavigationTab class which is the control
           for the navigation
  */

#ifndef NAVIGATIONTAB_H
#define NAVIGATIONTAB_H

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_NavigationTab;
class Packet;

/** The NavigationTab class is the control for the navigation of the
    Applanix.
    \brief Navigation control
  */
class NavigationTab :
  public Control,
  public Singleton<NavigationTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  NavigationTab(const NavigationTab& other);
  /// Assignment operator
  NavigationTab& operator = (const NavigationTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  NavigationTab();
  /// Destructor
  virtual ~NavigationTab();
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
  Ui_NavigationTab* mUi;
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

#endif // NAVIGATIONTAB_H
