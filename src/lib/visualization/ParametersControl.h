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

/** \file ParametersControl.h
    \brief This file defines the ParametersControl class which is the control
           for the parameters
  */

#ifndef PARAMETERSCONTROL_H
#define PARAMETERSCONTROL_H

#include <map>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_ParametersControl;
class Packet;

/** The ParametersControl class is the control for the parameters of the
    Applanix.
    \brief Parameters control
  */
class ParametersControl :
  public Control,
  public Singleton<ParametersControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ParametersControl(const ParametersControl& other);
  /// Assignment operator
  ParametersControl& operator = (const ParametersControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ParametersControl();
  /// Destructor
  virtual ~ParametersControl();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_ParametersControl* mUi;
  /// Mapping for ZUPD control messages
  std::map<uint16_t, std::string> mZUPDCtrlMsg;
  /// Mapping for navigation control messages
  std::map<uint8_t, std::string> mNavModeMsg;
  /// Mapping for time types messages
  std::map<uint8_t, std::string> mTimeTypesMsg;
  /// Mapping for distance types messages
  std::map<uint8_t, std::string> mDistanceTypeMsg;
  /// Mapping for autostart messages
  std::map<uint8_t, std::string> mAutoStartMsg;
  /// Mapping for multi-env messages
  std::map<uint8_t, std::string> mMultiEnvMsg;
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

#endif // PARAMETERSCONTROL_H
