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

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "types/Group.h"

class Ui_GAMSControl;

/** The GAMSControl class is the control for the GAMS solution of the Applanix.
    \brief GAMS solution control
  */
class GAMSControl :
  public Control,
  public Singleton<GAMSControl> {
Q_OBJECT

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
  Ui_GAMSControl* mpUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Applanix group read
  void groupRead(const Group* group);
  /** @}
    */

};

#endif // GAMSCONTROL_H
