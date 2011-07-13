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

/** \file TimeControl.h
    \brief This file defines the TimeControl class which is the control
           for the time
  */

#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "types/Group.h"

class Ui_TimeControl;

/** The TimeControl class is the control for the time of the Applanix.
    \brief Time control
  */
class TimeControl :
  public Control,
  public Singleton<TimeControl> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  TimeControl();
  /// Destructor
  virtual ~TimeControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_TimeControl* mpUi;
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

#endif // TIMECONTROL_H
