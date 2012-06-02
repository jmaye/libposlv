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

#include "visualization/MapTab.h"

#include <sstream>

#include "types/Packet.h"
#include "types/Group.h"
#include "types/VehicleNavigationSolution.h"

#include "ui_MapTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MapTab::MapTab() :
    mUi(new Ui_MapTab()) {
  mUi->setupUi(this);
  mTimer.setInterval(1000);
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

MapTab::~MapTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MapTab::readPacket(boost::shared_ptr<Packet> packet) {
    if (packet->instanceOfGroup())
      if (packet->groupCast().instanceOf<VehicleNavigationSolution>()) {
        const VehicleNavigationSolution& msg =
          packet->groupCast().typeCast<VehicleNavigationSolution>();
        mLatitude = msg.mLatitude;
        mLongitude = msg.mLongitude;
        mTimer.start();
      }
}

void MapTab::timerTimeout() {
  std::stringstream url;
  std::cout << "Loading map" << std::endl;
  if (mUi->openRadioButton->isChecked())
    url << "http://www.openstreetmap.org/?mlat=" << mLatitude << "&mlon="
      << mLongitude << "&zoom=12";
  else
    url << "http://maps.googleapis.com/maps/api/staticmap?center="
      << mLongitude << "," << mLatitude << "&size=" << mUi->webView->width()
      << "x" << mUi->webView->height() << "&zoom=17&sensor=true";
  mUi->webView->load(QUrl(url.str().c_str()));
}
