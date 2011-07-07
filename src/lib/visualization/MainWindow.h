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

/** \file MainWindow.h
    \brief This file defines the MainWindow class which is the main window
           for live visualization of Applanix data
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QTimer>

class Ui_MainWindow;

/** The MainWindow class is the main window for live visualization of
    Applanix data.
    \brief Live visualization of Applanix data
  */
class MainWindow :
  public QMainWindow {
Q_OBJECT

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MainWindow(double readTime = 1.0);
  /// Destructor
  ~MainWindow();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_MainWindow* mpUi;
  /// Timer for reading through network
  QTimer* mpTimer;
  /// Time for reading
  double mReadTime;
  /** @}
    */

protected slots:
  /** \name Protected members
    @{
    */
  /// Update function for the timer
  void update();
  /** @}
    */

};

#endif // MAINWINDOW_H
