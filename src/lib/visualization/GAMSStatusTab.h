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

/** \file GAMSStatusTab.h
    \brief This file defines the GAMSStatusTab class which is the control
           for the GAMS solution
  */

#ifndef GAMSSTATUSTAB_H
#define GAMSSTATUSTAB_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_GAMSStatusTab;
class Packet;

/** The GAMSStatusTab class is the control for the GAMS solution of the
    Applanix.
    \brief GAMS solution control
  */
class GAMSStatusTab :
  public Control,
  public Singleton<GAMSStatusTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GAMSStatusTab(const GAMSStatusTab& other);
  /// Assignment operator
  GAMSStatusTab& operator = (const GAMSStatusTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  GAMSStatusTab();
  /// Destructor
  virtual ~GAMSStatusTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields();
  /// Disable the fields
  void disableFields();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_GAMSStatusTab* mUi;
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

#endif // GAMSSTATUSTAB_H
