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

/** \file FDIRControl.h
    \brief This file defines the FDIRControl class which is the control
           for the FDIR
  */

#ifndef FDIRCONTROL_H
#define FDIRCONTROL_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "types/Packet.h"

class Ui_FDIRControl;
class Group;

/** The FDIRControl class is the control for the FDIR of the Applanix.
    \brief FDIR control
  */
class FDIRControl :
  public Control,
  public Singleton<FDIRControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  FDIRControl(const FDIRControl& other);
  /// Assignment operator
  FDIRControl& operator = (const FDIRControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  FDIRControl();
  /// Destructor
  virtual ~FDIRControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_FDIRControl* mUi;
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

#endif // FDIRCONTROL_H
