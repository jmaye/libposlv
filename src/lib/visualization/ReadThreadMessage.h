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

/** \file ReadThreadMessage.h
    \brief This file defines the ReadThreadMessage class which handles the
           communication with the Applanix for reading messages
  */

#ifndef READTHREADMESSAGE_H
#define READTHREADMESSAGE_H

#include "base/Singleton.h"
#include "types/Message.h"
#include "com/POSLVDisplay.h"

#include <QtCore/QThread>

/** The ReadThreadMessage class handles the communication with the Applanix for
    reading messages.
    \brief Read thread for messages
  */
class ReadThreadMessage :
  public QThread,
  public Singleton<ReadThreadMessage> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ReadThreadMessage(double pollTime = 0.5);
  /// Destructor
  virtual ~ReadThreadMessage();
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
  /// Device for reading through the network (UDP)
  POSLVDisplay mDevice;
  /// Storage for the Message pointers
  std::list<const Message*> mMessagePtrList;
  /** @}
    */

signals:
  /** \name Signals
    @{
    */
  /// Emitted when an Applanix message is read
  void messageRead(const Message* message);
  /** @}
    */

};

#endif // READTHREADMESSAGE_H
