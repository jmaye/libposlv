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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file control.cpp
    \brief This file is a testing binary for controlling the Applanix POS LV.
  */

#include <QtGui/QApplication>
#include <QtCore/QThread>

#include "com/TCPConnectionClient.h"
#include "visualization/TCPCom.h"
#include "sensor/POSLVComTCP.h"
#include "visualization/MainWindow.h"
#include "visualization/AutoCalibrationTab.h"
#include "visualization/AcknowledgeTab.h"

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("Applanix POS LV Control");
  AutoCalibrationTab autoCalibrationTab;
  AcknowledgeTab acknowledgeTab;
  mainWindow.addControl("Auto Calibration", autoCalibrationTab);
  mainWindow.addControl("Acknowledge", acknowledgeTab);
  TCPConnectionClient connection("129.132.39.171", 5601);
  POSLVComTCP device(connection);
  TCPCom com(device);
  QThread* comThread = new QThread;
  com.moveToThread(comThread);
  comThread->start();
  QObject::connect(&com,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::connect(&autoCalibrationTab,
    SIGNAL(writePacket(boost::shared_ptr<Packet>)),
    &com,
    SLOT(writePacket(boost::shared_ptr<Packet>)));
  QObject::connect(&com,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &acknowledgeTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  mainWindow.show();
  const int ret = application.exec();
  return ret;
}
