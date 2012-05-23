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

/** \file TCPCom.h
    \brief This file defines the TCPCom class which handles TCP connection for
           the UI.
  */

#ifndef TCPCOM_H
#define TCPCOM_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <QtCore/QMetaType>

#include <boost/shared_ptr.hpp>

class POSLVComTCP;
class Packet;

Q_DECLARE_METATYPE(boost::shared_ptr<Packet>);

/** The TCPCom class handles TCP connection for the UI.
    \brief TCP Communication for Applanix UI
  */
class TCPCom :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  TCPCom(const TCPCom& other);
  /// Assignment operator
  TCPCom& operator = (const TCPCom& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  TCPCom(POSLVComTCP& device, double pollingTime = 500);
  /// Destructor
  virtual ~TCPCom();
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
  POSLVComTCP& mDevice;
  /// Read timer
  QTimer mReadTimer;
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
  /// Send a packet to the Applanix
  void writePacket(boost::shared_ptr<Packet> packet);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Packet read
  void readPacket(boost::shared_ptr<Packet> packet);
  /// Device connected
  void deviceConnected(bool connected);
  /** @}
    */

};

#endif // TCPCOM_H
