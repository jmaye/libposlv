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

#include "visualization/MainWindow.h"

#include "ui_MainWindow.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MainWindow::MainWindow(double readTime) :
  mpUi(new Ui_MainWindow()),
  mReadTime(readTime) {
  mpUi->setupUi(this);
  mpTimer = new QTimer(this);
  connect(mpTimer, SIGNAL(timeout()), this, SLOT(update()));
  mpTimer->start(mReadTime);
  mpUi->statusbar->showMessage(tr("Disconnected"));
}

MainWindow::~MainWindow() {
  delete mpTimer;
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MainWindow::update() {
}
