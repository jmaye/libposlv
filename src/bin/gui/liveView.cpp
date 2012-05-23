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

/** \file liveView.cpp
    \brief This file is a testing binary for live visualization of the Applanix
           POS LV.
  */

#include <QtGui/QApplication>
#include <QtCore/QThread>

#include "visualization/MainWindow.h"
#include "com/UDPConnectionServer.h"
#include "sensor/POSLVComUDP.h"
#include "visualization/UDPReader.h"
#include "visualization/NavigationControl.h"
#include "visualization/PrimaryGPSControl.h"
#include "visualization/SecondaryGPSControl.h"
#include "visualization/GAMSControl.h"
#include "visualization/IMUControl.h"
#include "visualization/DMIControl.h"
#include "visualization/IINControl.h"
#include "visualization/StatusControl.h"
#include "visualization/FDIRControl.h"
#include "visualization/CalibrationControl.h"
#include "visualization/VersionControl.h"
#include "visualization/TimeControl.h"
#include "visualization/ParametersControl.h"
#include "visualization/PortControl.h"

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  NavigationControl navigationControl;
  PrimaryGPSControl primaryGPSControl;
  SecondaryGPSControl secondaryGPSControl;
  GAMSControl gamsControl;
  IMUControl imuControl;
  DMIControl dmiControl;
  IINControl iinControl;
  StatusControl statusControl;
  FDIRControl fdirControl;
  CalibrationControl calibrationControl;
  VersionControl versionControl;
  TimeControl timeControl;
  ParametersControl parametersControl;
  PortControl portControl;
  mainWindow.addControl("Navigation", navigationControl);
  mainWindow.addControl("Primary GPS", primaryGPSControl);
  mainWindow.addControl("Secondary GPS", secondaryGPSControl);
  mainWindow.addControl("GAMS", gamsControl);
  mainWindow.addControl("IMU", imuControl);
  mainWindow.addControl("DMI", dmiControl);
  mainWindow.addControl("IIN", iinControl);
  mainWindow.addControl("Status", statusControl);
  mainWindow.addControl("FDIR", fdirControl);
  mainWindow.addControl("Calibration", calibrationControl);
  mainWindow.addControl("Version", versionControl);
  mainWindow.addControl("Time", timeControl);
  mainWindow.addControl("Parameters", parametersControl);
  mainWindow.addControl("Ports", portControl);
  UDPConnectionServer connection(5600);
  POSLVComUDP device(connection);
  UDPReader reader(device);
  QThread* readerThread = new QThread;
  reader.moveToThread(readerThread);
  readerThread->start();
  QObject::connect(&reader,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &statusControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibrationControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &parametersControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &portControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  mainWindow.show();
  const int ret = application.exec();
  QObject::disconnect(&reader,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &statusControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibrationControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &parametersControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &portControl,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  return ret;
}
