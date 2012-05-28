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
#include "visualization/NavigationTab.h"
#include "visualization/PrimaryGPSStatusTab.h"
#include "visualization/SecondaryGPSStatusTab.h"
#include "visualization/GAMSStatusTab.h"
#include "visualization/IMUDataTab.h"
#include "visualization/DMIDataTab.h"
#include "visualization/IINStatusTab.h"
#include "visualization/GeneralStatusTab.h"
#include "visualization/FDIRTab.h"
#include "visualization/CalibratedInstallationParamsTab.h"
#include "visualization/VersionTab.h"
#include "visualization/TimeStatusTab.h"
//#include "visualization/ParametersControl.h"
//#include "visualization/PortControl.h"

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  NavigationTab navigationTab;
  PrimaryGPSStatusTab primaryGPSStatusTab;
  SecondaryGPSStatusTab secondaryGPSStatusTab;
  GAMSStatusTab gamsStatusTab;
  IMUDataTab imuDataTab;
  DMIDataTab dmiDataTab;
  IINStatusTab iinStatusTab;
  GeneralStatusTab generalStatusTab;
  FDIRTab fdirTab;
  CalibratedInstallationParamsTab calibratedInstallationParamsTab;
  VersionTab versionTab;
  TimeStatusTab timeStatusTab;
  //ParametersControl parametersControl;
  //PortControl portControl;
  mainWindow.addControl("Navigation Data", navigationTab);
  mainWindow.addControl("Primary GPS Status", primaryGPSStatusTab);
  mainWindow.addControl("Secondary GPS Status", secondaryGPSStatusTab);
  mainWindow.addControl("GAMS Status", gamsStatusTab);
  mainWindow.addControl("IMU Data", imuDataTab);
  mainWindow.addControl("DMI Data", dmiDataTab);
  mainWindow.addControl("IIN Status", iinStatusTab);
  mainWindow.addControl("General Status", generalStatusTab);
  mainWindow.addControl("FDIR", fdirTab);
  mainWindow.addControl("Calibration", calibratedInstallationParamsTab);
  mainWindow.addControl("Version", versionTab);
  mainWindow.addControl("Time", timeStatusTab);
  //mainWindow.addControl("Parameters", parametersControl);
  //mainWindow.addControl("Ports", portControl);
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
    &navigationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibratedInstallationParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
//  QObject::connect(&reader,
//    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
//    &parametersControl,
//    SLOT(readPacket(boost::shared_ptr<Packet>)));
//  QObject::connect(&reader,
//    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
//    &portControl,
//    SLOT(readPacket(boost::shared_ptr<Packet>)));
  mainWindow.show();
  const int ret = application.exec();
  QObject::disconnect(&reader,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibratedInstallationParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&reader,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
//  QObject::disconnect(&reader,
//    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
//    &parametersControl,
//    SLOT(readPacket(boost::shared_ptr<Packet>)));
//  QObject::disconnect(&reader,
//    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
//    &portControl,
//    SLOT(readPacket(boost::shared_ptr<Packet>)));
  return ret;
}
