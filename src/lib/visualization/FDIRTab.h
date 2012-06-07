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

/** \file FDIRTab.h
    \brief This file defines the FDIRTab class which is the control
           for the FDIR
  */

#ifndef FDIRTAB_H
#define FDIRTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_FDIRTab;
class Packet;

/** The FDIRTab class is the control for the FDIR of the Applanix.
    \brief FDIR control
  */
class FDIRTab :
  public Control,
  public Singleton<FDIRTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  FDIRTab(const FDIRTab& other);
  /// Assignment operator
  FDIRTab& operator = (const FDIRTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  FDIRTab();
  /// Destructor
  virtual ~FDIRTab();
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
  Ui_FDIRTab* mUi;
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

#endif // FDIRTAB_H
