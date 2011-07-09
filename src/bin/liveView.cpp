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

#include "visualization/MainWindow.h"
#include "visualization/NavigationControl.h"
#include "visualization/PrimaryGPSControl.h"
#include "visualization/SecondaryGPSControl.h"
#include "visualization/Aux1GPSControl.h"
#include "visualization/Aux2GPSControl.h"
#include "visualization/ReadThread.h"

#include <QtGui/QApplication>

int main(int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  NavigationControl navigationControl;
  PrimaryGPSControl primaryGPSControl;
  SecondaryGPSControl secondaryGPSControl;
  Aux1GPSControl aux1GPSControl;
  Aux2GPSControl aux2GPSControl;
  ReadThread::getInstance().start();

  mainWindow.addControl("Navigation", navigationControl);
  mainWindow.addControl("Primary GPS", primaryGPSControl);
  mainWindow.addControl("Secondary GPS", secondaryGPSControl);
  mainWindow.addControl("Auxiliary 1 GPS", aux1GPSControl);
  mainWindow.addControl("Auxiliary 2 GPS", aux2GPSControl);

  mainWindow.show();

  return application.exec();
}
