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

#include "visualization/MainWindow.h"
#include "visualization/Path3DTab.h"
#include "visualization/Path2DTab.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <logFile>" << std::endl;
    return 1;
  }
  QApplication application(argc, argv);
  MainWindow mainWindow;
  mainWindow.setWindowTitle("Applanix POS LV Path Viewer");
  std::ifstream logFile(argv[1]);
  Path2DTab path2DTab;
  Path3DTab path3DTab;
  mainWindow.addControl("2D Path", path2DTab);
  mainWindow.addControl("3D Path", path3DTab);
  mainWindow.show();
  const int ret = application.exec();
  return ret;
}
