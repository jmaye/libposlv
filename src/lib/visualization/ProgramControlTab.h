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

/** \file ProgramControlTab.h
    \brief This file defines the ProgramControlTab class which is the
           control for the program
  */

#ifndef PROGRAMCONTROLTAB_H
#define PROGRAMCONTROLTAB_H

#include <QtCore/QTimer>

#include <boost/shared_ptr.hpp>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_ProgramControlTab;
class Packet;

/** The ProgramControlTab class is the control for the program
    of the Applanix.
    \brief Program control
  */
class ProgramControlTab :
  public Control,
  public Singleton<ProgramControlTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ProgramControlTab(const ProgramControlTab& other);
  /// Assignment operator
  ProgramControlTab& operator = (const ProgramControlTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ProgramControlTab();
  /// Destructor
  virtual ~ProgramControlTab();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_ProgramControlTab* mUi;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Connect pressed
  void connectPressed();
  /// Disconnect pressed
  void disconnectPressed();
  /// Reset POS pressed
  void resetPOSPressed();
  /// Reset GAMS pressed
  void resetGAMSPressed();
  /// Shutdown pressed
  void shutdownPressed();
  /** @}
    */

signals:
  /** \name Signals
    @{
    */
  /// Connect to the POS
  void connect(bool connect);
  /// Sends a packet to the POS
  void writePacket(boost::shared_ptr<Packet> packet);
  /** @}
    */

};

#endif // PROGRAMCONTROLTAB_H
