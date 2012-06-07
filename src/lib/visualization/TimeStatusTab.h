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

/** \file TimeStatusTab.h
    \brief This file defines the TimeStatusTab class which is the control
           for the time
  */

#ifndef TIMESTATUSTAB_H
#define TIMESTATUSTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_TimeStatusTab;
class Packet;

/** The TimeStatusTab class is the control for the time of the Applanix.
    \brief Time control
  */
class TimeStatusTab :
  public Control,
  public Singleton<TimeStatusTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  TimeStatusTab(const TimeStatusTab& other);
  /// Assignment operator
  TimeStatusTab& operator = (const TimeStatusTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  TimeStatusTab();
  /// Destructor
  virtual ~TimeStatusTab();
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
  Ui_TimeStatusTab* mUi;
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

#endif // TIMESTATUSTAB_H
