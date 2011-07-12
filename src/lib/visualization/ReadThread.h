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

/** \file ReadThread.h
    \brief This file defines the ReadThread class which handles the
           communication with the Applanix
  */

#ifndef READTHREAD_H
#define READTHREAD_H

#include "base/Singleton.h"
#include "types/Group.h"
#include "com/POSLVDisplay.h"

#include <QtCore/QThread>
#include <QtCore/QTimer>

/** The ReadThread class handles the communication with the Applanix.
    \brief Read thread
  */
class ReadThread :
  public QThread,
  public Singleton<ReadThread> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ReadThread(double pollTime = 0.1);
  /// Destructor
  virtual ~ReadThread();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the polling time
  double getPollTime() const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Processing function
  void run();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Time frequency [s] to poll the network
  double mPollTime;
  /// Device for reading through the network
  POSLVDisplay mDevice;
  /// Storage for the Group pointers
  std::list<const Group*> mGroupPtrList;
  /// Timer for emptying the list
  QTimer* mpTimer;
  /** @}
    */

protected slots:
  /** \name Slots
    @{
    */
  /// Timer triggered
  void update();
  /** @}
    */

signals:
  /** \name Signals
    @{
    */
  /// Emitted when an Applanix group is read
  void groupRead(const Group* group);
  /// Emitted when the device is connected or disconnected
  void deviceConnected(bool connected);
  /** @}
    */

};

#endif // READTHREAD_H
