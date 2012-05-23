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

#include "visualization/TimeControl.h"

#include "types/PPSTimeRecoveryStatus.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_TimeControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeControl::TimeControl() :
    mUi(new Ui_TimeControl()) {
  mUi->setupUi(this);
}

TimeControl::~TimeControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TimeControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<PPSTimeRecoveryStatus>()) {
      const PPSTimeRecoveryStatus& msg =
        group.typeCast<PPSTimeRecoveryStatus>();
      mUi->gpsTimeSpinBox->setValue(msg.mTimeDistance.mTime1);
      mUi->posTimeSpinBox->setValue(msg.mTimeDistance.mTime2);
      mUi->distanceSpinBox->setValue(msg.mTimeDistance.mDistanceTag);
    }
  }
}
