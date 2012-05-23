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

/** \file AcknowledgeControl.h
    \brief This file defines the AcknowledgeControl class which is the
           control for acknowledge of the Applanix
  */

#ifndef ACKNOWLEDGECONTROL_H
#define ACKNOWLEDGECONTROL_H

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_AcknowledgeControl;
class Packet;

/** The AcknowledgeControl class is the control for the auto calibration of
    the Applanix.
    \brief Auto calibration control
  */
class AcknowledgeControl :
  public Control,
  public Singleton<AcknowledgeControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  AcknowledgeControl(const AcknowledgeControl& other);
  /// Assignment operator
  AcknowledgeControl& operator = (const AcknowledgeControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  AcknowledgeControl();
  /// Destructor
  virtual ~AcknowledgeControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_AcknowledgeControl* mUi;
  /// Mapping for the status messages
  std::map<uint16_t, std::string> mStatusMsg;
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

#endif // ACKNOWLEDGECONTROL_H
