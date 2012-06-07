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

/** \file CalibratedInstallationParamsTab.h
    \brief This file defines the CalibratedInstallationParamsTab class which is
           the control for the calibrated installation parameters
  */

#ifndef CALIBRATEDINSTALLATIONPARAMSTAB_H
#define CALIBRATEDINSTALLATIONPARAMSTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_CalibratedInstallationParamsTab;
class Packet;

/** The CalibratedInstallationParamsTab class is the control for the calibrated
    installation parameters of the Applanix.
    \brief Calibrated installation parameters control
  */
class CalibratedInstallationParamsTab :
  public Control,
  public Singleton<CalibratedInstallationParamsTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  CalibratedInstallationParamsTab(const CalibratedInstallationParamsTab& other);
  /// Assignment operator
  CalibratedInstallationParamsTab& operator = (const
    CalibratedInstallationParamsTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  CalibratedInstallationParamsTab();
  /// Destructor
  virtual ~CalibratedInstallationParamsTab();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Enable the fields
  void enableFields(bool enable);;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_CalibratedInstallationParamsTab* mUi;
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

#endif // CALIBRATEDINSTALLATIONPARAMSTAB_H
