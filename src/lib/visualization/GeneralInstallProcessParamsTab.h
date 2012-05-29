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

/** \file GeneralInstallProcessParamsTab.h
    \brief This file defines the GeneralInstallProcessParamsTab class which is
           the control for the general installation parameters.
  */

#ifndef GENERALINSTALLPROCESSPARAMSTAB_H
#define GENERALINSTALLPROCESSPARAMSTAB_H

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_GeneralInstallProcessParamsTab;
class Packet;

/** The GeneralInstallProcessParamsTab class is the control for the general
    installation parameters of the Applanix.
    \brief General installation parameters control
  */
class GeneralInstallProcessParamsTab :
  public Control,
  public Singleton<GeneralInstallProcessParamsTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GeneralInstallProcessParamsTab(const GeneralInstallProcessParamsTab& other);
  /// Assignment operator
  GeneralInstallProcessParamsTab& operator = (const
    GeneralInstallProcessParamsTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  GeneralInstallProcessParamsTab();
  /// Destructor
  virtual ~GeneralInstallProcessParamsTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields(bool enable);
  /// Sets readonly fields
  void setReadOnlyFields(bool readonly);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_GeneralInstallProcessParamsTab* mUi;
  /// Specifies if the tab is in control mode
  bool mControlMode;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(boost::shared_ptr<Packet> packet);
  /// Apply pressed
  void applyPressed();
  /// Device connected
  void deviceConnected(bool connected);
  /** @}
    */

};

#endif // GENERALINSTALLPROCESSPARAMSTAB_H
