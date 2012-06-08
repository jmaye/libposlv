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

/** \file playback.cpp
    \brief This file is a testing binary for playback of Applanix log files
           and visualization.
  */

#include <string>
#include <fstream>
#include <iostream>

#include <QtGui/QApplication>
#include <QtCore/QThread>
#include <QtCore/QMetaType>

#include "sensor/BinaryLogReader.h"
#include "visualization/LogReader.h"
#include "visualization/MainWindow.h"
#include "visualization/NavigationTab.h"
#include "visualization/PrimaryGPSStatusTab.h"
#include "visualization/SecondaryGPSStatusTab.h"
#include "visualization/GAMSStatusTab.h"
#include "visualization/IMUDataTab.h"
#include "visualization/DMIDataTab.h"
#include "visualization/IINStatusTab.h"
#include "visualization/GeneralStatusTab.h"
#include "visualization/FDIRTab.h"
#include "visualization/VersionTab.h"
#include "visualization/TimeStatusTab.h"
#include "visualization/GeneralInstallProcessParamsTab.h"
#include "visualization/GAMSInstallParamsTab.h"
#include "visualization/AidingSensorInstallParamsTab.h"
#include "visualization/UserAccuracySpecTab.h"
#include "visualization/IPControlTab.h"
#include "visualization/NavigationModeControlTab.h"
#include "visualization/MapTab.h"

Q_DECLARE_METATYPE(std::shared_ptr<Packet>);
Q_DECLARE_METATYPE(std::string);

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <logFile>" << std::endl;
    return 1;
  }
  qRegisterMetaType<std::shared_ptr<Packet> >();
  qRegisterMetaType<std::string>();
  QApplication application(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("Applanix POS LV Playback");
  NavigationTab navigationTab;
  PrimaryGPSStatusTab primaryGPSStatusTab;
  SecondaryGPSStatusTab secondaryGPSStatusTab;
  GAMSStatusTab gamsStatusTab;
  IMUDataTab imuDataTab;
  DMIDataTab dmiDataTab;
  IINStatusTab iinStatusTab;
  GeneralStatusTab generalStatusTab;
  FDIRTab fdirTab;
  VersionTab versionTab;
  TimeStatusTab timeStatusTab;
  GeneralInstallProcessParamsTab generalInstallProcessParamsTab;
  GAMSInstallParamsTab gamsInstallParamsTab;
  AidingSensorInstallParamsTab aidingSensorInstallParamsTab;
  UserAccuracySpecTab userAccuracySpecTab;
  IPControlTab ipControlTab;
  NavigationModeControlTab navigationModeControlTab;
  MapTab mapTab;
  mainWindow.addControl("Navigation Data", navigationTab);
  mainWindow.addControl("Primary GPS Status", primaryGPSStatusTab);
  mainWindow.addControl("Secondary GPS Status", secondaryGPSStatusTab);
  mainWindow.addControl("GAMS Status", gamsStatusTab);
  mainWindow.addControl("IMU Data", imuDataTab);
  mainWindow.addControl("DMI Data", dmiDataTab);
  mainWindow.addControl("IIN Status", iinStatusTab);
  mainWindow.addControl("General Status", generalStatusTab);
  mainWindow.addControl("FDIR", fdirTab);
  mainWindow.addControl("Version", versionTab);
  mainWindow.addControl("Time", timeStatusTab);
  mainWindow.addControl("General Parameters", generalInstallProcessParamsTab);
  mainWindow.addControl("GAMS Parameters", gamsInstallParamsTab);
  mainWindow.addControl("DMI Parameters", aidingSensorInstallParamsTab);
  mainWindow.addControl("User Accuracy", userAccuracySpecTab);
  mainWindow.addControl("IP Setup", ipControlTab);
  mainWindow.addControl("Navigation Mode", navigationModeControlTab);
  mainWindow.addControl("Map", mapTab);
  std::ifstream logFile(argv[1]);
  BinaryLogReader binaryLogReader(logFile);
  LogReader logReader(binaryLogReader);
  QThread* readerThread = new QThread;
  logReader.moveToThread(readerThread);
  readerThread->start();
  QObject::connect(&logReader,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  QObject::connect(&logReader,
    SIGNAL(comException(const std::string&)),
    &mainWindow,
    SLOT(comException(const std::string&)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &navigationTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &generalInstallProcessParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &gamsInstallParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &aidingSensorInstallParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &userAccuracySpecTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &ipControlTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &navigationModeControlTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&navigationTab,
    SIGNAL(updatePosition(double, double, double)),
    &mapTab,
    SLOT(updatePosition(double, double, double)));
  QObject::connect(&navigationTab,
    SIGNAL(updateUncertainty(double, double, double)),
    &mapTab,
    SLOT(updateUncertainty(double, double, double)));
  mainWindow.show();
  const int ret = application.exec();
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &navigationTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &primaryGPSStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &secondaryGPSStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &gamsStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &imuDataTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &dmiDataTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &iinStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &generalStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &fdirTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &versionTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &timeStatusTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &generalInstallProcessParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &gamsInstallParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &aidingSensorInstallParamsTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &userAccuracySpecTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &ipControlTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &navigationModeControlTab,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&navigationTab,
    SIGNAL(updatePosition(double, double, double)),
    &mapTab,
    SLOT(updatePosition(double, double, double)));
  QObject::disconnect(&navigationTab,
    SIGNAL(updateUncertainty(double, double, double)),
    &mapTab,
    SLOT(updateUncertainty(double, double, double)));
  QObject::disconnect(&logReader,
    SIGNAL(comException(const std::string&)),
    &mainWindow,
    SLOT(comException(const std::string&)));
  QObject::disconnect(&logReader,
    SIGNAL(deviceConnected(bool)),
    &mainWindow,
    SLOT(deviceConnected(bool)));
  return ret;
}
