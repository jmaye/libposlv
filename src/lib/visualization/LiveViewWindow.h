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

/** \file LiveViewWindow.h
    \brief This file defines the LiveViewWindow class which is the main window
           for live visualization of Applanix data
  */

#ifndef LIVEVIEWWINDOW_H
#define LIVEVIEWWINDOW_H

#include "com/POSLVDisplay.h"

#include <QtGui/QMainWindow>
#include <QtCore/QTimer>

class Ui_LiveViewWindow;

/** The LiveViewWindow class is the main window for live visualization of
    Applanix data.
    \brief Live visualization of Applanix data
  */
class LiveViewWindow :
  public QMainWindow,
  public POSLVDisplay {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LiveViewWindow(uint16_t port = 5600, double timeout = 2.5,
    double readTime = 10.0);
  /// Destructor
  ~LiveViewWindow();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Read update
  double mReadTime;
  /// Pointer to the UI
  Ui_LiveViewWindow* mpUi;
  /// Timer for reading the port
  QTimer* mTimer;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Triggered by the timer
  void update();
  /** @}
    */

};

#endif // LIVEVIEWWINDOW_H
