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

/** \file view.cpp
    \brief This file is a testing binary for live visualization and control of
           the Applanix POS LV.
  */

#include <QtGui/QApplication>
#include <QtCore/QThread>
#include <QtCore/QMetaType>

#include "visualization/MainWindow.h"
#include "com/UDPConnectionServer.h"
#include "sensor/POSLVComUDP.h"
#include "com/TCPConnectionClient.h"
#include "sensor/POSLVComTCP.h"
#include "visualization/UDPCom.h"
#include "visualization/TCPCom.h"
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
#include "visualization/ProgramControlTab.h"
#include "visualization/GeneralInstallProcessParamsTab.h"
#include "visualization/GAMSInstallParamsTab.h"
#include "visualization/AidingSensorInstallParamsTab.h"
#include "visualization/UserAccuracySpecTab.h"
#include "visualization/ZUPDControlTab.h"
#include "visualization/IPControlTab.h"
#include "visualization/GravityControlTab.h"
#include "visualization/NavigationModeControlTab.h"
#include "visualization/SaveRestoreControlTab.h"
#include "visualization/AutoCalibrationTab.h"
#include "visualization/AcknowledgeTab.h"

Q_DECLARE_METATYPE(boost::shared_ptr<Packet>);

int main(int argc, char** argv) {
  qRegisterMetaType<boost::shared_ptr<Packet> >();
  QApplication application(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("Applanix POS LV View");
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
  ProgramControlTab programControlTab;
  GeneralInstallProcessParamsTab generalInstallProcessParamsTab;
  GAMSInstallParamsTab gamsInstallParamsTab;
  AidingSensorInstallParamsTab aidingSensorInstallParamsTab;
  UserAccuracySpecTab userAccuracySpecTab;
  ZUPDControlTab zupdControlTab;
  IPControlTab ipControlTab;
  GravityControlTab gravityControlTab;
  NavigationModeControlTab navigationModeControlTab;
  SaveRestoreControlTab saveRestoreControlTab;
  AutoCalibrationTab autoCalibrationTab;
  AcknowledgeTab acknowledgeTab;
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
  mainWindow.addControl("Program Control", programControlTab);
  mainWindow.addControl("General Parameters", generalInstallProcessParamsTab);
  mainWindow.addControl("GAMS Parameters", gamsInstallParamsTab);
  mainWindow.addControl("DMI Parameters", aidingSensorInstallParamsTab);
  mainWindow.addControl("User Accuracy", userAccuracySpecTab);
  mainWindow.addControl("ZUPD Parameters", zupdControlTab);
  mainWindow.addControl("IP Setup", ipControlTab);
  mainWindow.addControl("Gravity Setup", gravityControlTab);
  mainWindow.addControl("Navigation Mode", navigationModeControlTab);
  mainWindow.addControl("Save/Restore", saveRestoreControlTab);
  mainWindow.addControl("Auto Calibration", autoCalibrationTab);
  mainWindow.addControl("Acknowledge", acknowledgeTab);
  UDPConnectionServer udpConnection(5600);
  POSLVComUDP udpDevice(udpConnection);
  UDPCom udpCom(udpDevice);
  QThread* udpThread = new QThread;
  udpCom.moveToThread(udpThread);
  udpThread->start();
  TCPConnectionClient tcpConnection("129.132.39.171", 5601);
  POSLVComTCP tcpDevice(tcpConnection);
  TCPCom tcpCom(tcpDevice);
  QThread* tcpThread = new QThread;
  tcpCom.moveToThread(tcpThread);
  tcpThread->start();
  QObject::connect(&programControlTab,
    SIGNAL(connect(bool)),
    &tcpCom,
    SLOT(connect(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &programControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &generalInstallProcessParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &gamsInstallParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &aidingSensorInstallParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &userAccuracySpecTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &zupdControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &ipControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &gravityControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &navigationModeControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &saveRestoreControlTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &autoCalibrationTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &autoCalibrationTab,
    SLOT(deviceConnected(bool)));
  QObject::connect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibratedInstallationParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalInstallProcessParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsInstallParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &aidingSensorInstallParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &userAccuracySpecTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &zupdControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &ipControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gravityControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationModeControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &autoCalibrationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::connect(&programControlTab,
    SIGNAL(writePacket(boost::shared_ptr<Packet>)),
    &tcpCom,
    SLOT(writePacket(boost::shared_ptr<Packet>)));
  mainWindow.show();
  const int ret = application.exec();
  QObject::disconnect(&programControlTab,
    SIGNAL(connect(bool)),
    &tcpCom,
    SLOT(connect(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &programControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &generalInstallProcessParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &gamsInstallParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &aidingSensorInstallParamsTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &userAccuracySpecTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &zupdControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &ipControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &gravityControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &navigationModeControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &saveRestoreControlTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &autoCalibrationTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&tcpCom,
    SIGNAL(deviceConnected(bool)),
    &autoCalibrationTab,
    SLOT(deviceConnected(bool)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &calibratedInstallationParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &generalInstallProcessParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gamsInstallParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &aidingSensorInstallParamsTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &userAccuracySpecTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &zupdControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &ipControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &gravityControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &navigationModeControlTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  QObject::disconnect(&udpCom,
    SIGNAL(readPacket(boost::shared_ptr<Packet>)),
    &autoCalibrationTab,
    SLOT(readPacket(boost::shared_ptr<Packet>)));
  return ret;
}
