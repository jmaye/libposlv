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

/** \file pathViewer.cpp
    \brief This file is a testing binary for plotting an Applanix run on a map.
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
#include "visualization/PathBuilder.h"
#include "visualization/Path3DTab.h"
#include "visualization/Path2DTab.h"

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
  mainWindow.setWindowTitle("Applanix POS LV Path Viewer");
  std::ifstream logFile(argv[1]);
  BinaryLogReader binaryLogReader(logFile);
  LogReader logReader(binaryLogReader, 0);
  QThread* readerThread = new QThread;
  logReader.moveToThread(readerThread);
  readerThread->start();
  PathBuilder pathBuilder;
  Path2DTab path2DTab;
  Path3DTab path3DTab;
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
    &pathBuilder,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::connect(&logReader,
    SIGNAL(eof()),
    &pathBuilder,
    SLOT(eof()));
  QObject::connect(&logReader,
    SIGNAL(start()),
    &pathBuilder,
    SLOT(start()));
  QObject::connect(&logReader,
    SIGNAL(start()),
    &path3DTab,
    SLOT(start()));
  QObject::connect(&pathBuilder,
    SIGNAL(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)),
    &path3DTab,
    SLOT(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)));
  QObject::connect(&logReader,
    SIGNAL(start()),
    &path2DTab,
    SLOT(start()));
  QObject::connect(&pathBuilder,
    SIGNAL(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)),
    &path2DTab,
    SLOT(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)));
  mainWindow.addControl("2D Path", path2DTab);
  mainWindow.addControl("3D Path", path3DTab);
  mainWindow.show();
  const int ret = application.exec();
  QObject::disconnect(&logReader,
    SIGNAL(readPacket(std::shared_ptr<Packet>)),
    &pathBuilder,
    SLOT(readPacket(std::shared_ptr<Packet>)));
  QObject::disconnect(&logReader,
    SIGNAL(eof()),
    &pathBuilder,
    SLOT(eof()));
  QObject::disconnect(&logReader,
    SIGNAL(start()),
    &pathBuilder,
    SLOT(start()));
  QObject::disconnect(&logReader,
    SIGNAL(start()),
    &path3DTab,
    SLOT(start()));
  QObject::disconnect(&pathBuilder,
    SIGNAL(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)),
    &path3DTab,
    SLOT(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)));
  QObject::disconnect(&logReader,
    SIGNAL(start()),
    &path2DTab,
    SLOT(start()));
  QObject::disconnect(&pathBuilder,
    SIGNAL(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)),
    &path2DTab,
    SLOT(path(const std::vector<Eigen::Matrix<double, 3, 1> >&)));
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
