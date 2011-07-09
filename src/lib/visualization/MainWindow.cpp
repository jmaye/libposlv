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

#include "visualization/ReadThread.h"
#include "ui_MainWindow.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MainWindow::MainWindow() :
  mpUi(new Ui_MainWindow()) {
  mpUi->setupUi(this);
  while (mpUi->tabsWidget->count())
    mpUi->tabsWidget->removeTab(0);

  mpUi->statusBar->showMessage("Disconnected");

  connect(&ReadThread::getInstance(), SIGNAL(deviceConnected(bool)), this,
    SLOT(deviceConnected(bool)));
}

MainWindow::~MainWindow() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MainWindow::addControl(const QString& title, Control& control) {
  mpUi->tabsWidget->addTab(&control, title);
  if (!control.getMenu().isEmpty())
    mpUi->menuBar->addMenu(&control.getMenu())->setText(title);
}

void MainWindow::deviceConnected(bool connected) {
  if (connected == true)
    mpUi->statusBar->showMessage("Connected");
  else
    mpUi->statusBar->showMessage("Disconnected");
}
