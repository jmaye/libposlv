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

/** \file Reader.h
    \brief This file defines the Reader class which continuously polls for
           packets from the Applanix device
  */

#ifndef READER_H
#define READER_H

#include <QtCore/QObject>
#include <QtCore/QTimer>

#include "base/Singleton.h"
#include "sensor/POSLVComUDP.h"
#include "types/Packet.h"

/** The Reader class continuously polls for packets from the Applanix.
    \brief Reader for Applanix
  */
class Reader :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Reader(const Reader& other);
  /// Assignment operator
  Reader& operator = (const Reader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs reader with polling time and device
  Reader(POSLVComUDP& device, double pollingTime = 500);
  /// Destructor
  virtual ~Reader();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the polling time
  double getPollingTime() const;
  /// Sets the polling time
  void setPollingTime(double pollingTime);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Device
  POSLVComUDP& mDevice;
  /// Timer
  QTimer mTimer;
  /// Polling time
  double mPollingTime;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Timeout of the timer
  void timerTimeout();
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Packet read
  void packetRead(boost::shared_ptr<Packet> packet);
  /// Device connected
  void deviceConnected(bool connected);
  /** @}
    */

};

#endif // READER_H
