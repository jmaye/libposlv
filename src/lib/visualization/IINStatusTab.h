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

/** \file IINStatusTab.h
    \brief This file defines the IINStatusTab class which is the control
           for the IIN solution
  */

#ifndef IINSTATUSTAB_H
#define IINSTATUSTAB_H

#include <memory>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_IINStatusTab;
class Packet;

/** The IINStatusTab class is the control for the IIN solution of the Applanix.
    \brief IIN solution control
  */
class IINStatusTab :
  public Control,
  public Singleton<IINStatusTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  IINStatusTab(const IINStatusTab& other);
  /// Assignment operator
  IINStatusTab& operator = (const IINStatusTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  IINStatusTab();
  /// Destructor
  virtual ~IINStatusTab();
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
  Ui_IINStatusTab* mUi;
  /// Mapping for the status messages
  std::map<uint8_t, std::string> mStatusMsg;
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

#endif // IINSTATUSTAB_H
