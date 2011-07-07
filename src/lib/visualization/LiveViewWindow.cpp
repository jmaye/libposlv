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

#include "visualization/LiveViewWindow.h"

#include "ui_LiveViewWindow.h"
#include "types/VehicleNavigationSolution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LiveViewWindow::LiveViewWindow(uint16_t port, double timeout, double readTime) :
  POSLVDisplay(port, timeout),
  mReadTime(readTime),
  mpUi(new Ui_LiveViewWindow()) {
  mpUi->setupUi(this);
  open();
  mTimer = new QTimer(this);
  connect(mTimer, SIGNAL(timeout()), this, SLOT(update()));
  mTimer->start(mReadTime);
}

LiveViewWindow::~LiveViewWindow() {
  delete mTimer;
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void LiveViewWindow::update() {
  const Group* read = readGroup();
  if (read != NULL) {
    if (read->instanceOf<VehicleNavigationSolution>() == true) {
      const VehicleNavigationSolution& msg =
        read->typeCast<VehicleNavigationSolution>();
      mpUi->latitudeSpinBox->setValue(msg.mLatitude);
      mpUi->longitudeSpinBox->setValue(msg.mLongitude);
    }
    delete read;
  }
}
