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

#include "visualization/ReadThreadGroup.h"
#include "types/PPSTimeRecoveryStatus.h"
#include "ui_TimeControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeControl::TimeControl() :
  mpUi(new Ui_TimeControl()) {
  mpUi->setupUi(this);

  connect(&ReadThreadGroup::getInstance(), SIGNAL(groupRead(const Group*)),
    this, SLOT(groupRead(const Group*)));
}

TimeControl::~TimeControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TimeControl::groupRead(const Group* group) {
  if (group->instanceOf<PPSTimeRecoveryStatus>() == true) {
    const PPSTimeRecoveryStatus& msg = group->typeCast<PPSTimeRecoveryStatus>();
    mpUi->gpsTimeSpinBox->setValue(msg.mTimeDistance.mTime1);
    mpUi->posTimeSpinBox->setValue(msg.mTimeDistance.mTime2);
    mpUi->distanceSpinBox->setValue(msg.mTimeDistance.mDistanceTag);
  }
}
