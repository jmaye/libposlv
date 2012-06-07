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

/** \file UDPCom.h
    \brief This file defines the UDPCom class which handles UDP communication
           with the POS.
  */

#ifndef UDPCOM_H
#define UDPCOM_H

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QTimer>

class POSLVComUDP;
class Packet;

/** The UDPCom class handles UDP communication with the Applanix.
    \brief UDP communication with the Applanix
  */
class UDPCom :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  UDPCom(const UDPCom& other);
  /// Assignment operator
  UDPCom& operator = (const UDPCom& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs reader with polling time and device
  UDPCom(POSLVComUDP& device, double pollingTime = 1);
  /// Destructor
  virtual ~UDPCom();
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
  void readPacket(std::shared_ptr<Packet> packet);
  /// Com exception
  void comException(const std::string& msg);
  /** @}
    */

};

#endif // UDPCOM_H
