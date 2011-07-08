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

/** \file NetworkProcess.h
    \brief This file defines the NetworkProcess class which handles the
           communication with the Applanix
  */

#ifndef NETWORKPROCESS_H
#define NETWORKPROCESS_H

#include "base/Singleton.h"
#include "types/Group.h"
#include "com/POSLVDisplay.h"

#include <QtGui/QWidget>
#include <QtCore/QTimer>

/** The NetworkProcess class handles the communication with the Applanix.
    \brief Network process
  */
class NetworkProcess :
  public QWidget,
  public Singleton<NetworkProcess> {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  NetworkProcess(double pollTime = 1.0);
  /// Destructor
  virtual ~NetworkProcess();
  /** @}
    */

  /** \name Accessors
    @{
    */
  double getPollTime() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Timer for polling the network
  QTimer* mpPollTimer;
  /// Time frequency [s] to poll the network
  double mPollTime;
  /// Device for reading through the network
  POSLVDisplay mDevice;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Processing function
  void update();
  /** @}
    */

signals:
  void groupRead(const Group* group);

};

#endif // NETWORKPROCESS_H
