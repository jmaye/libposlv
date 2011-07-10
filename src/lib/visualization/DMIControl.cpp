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

#include "visualization/DMIControl.h"

#include "visualization/ReadThread.h"
#include "types/TimeTaggedDMIData.h"
#include "ui_DMIControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DMIControl::DMIControl() :
  mpUi(new Ui_DMIControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[0] = "Invalid";
  mStatusMsg[1] = "Valid";
  mStatusMsg[2] = "Scale factor change";

  mTypeMsg[0] = "None";
  mTypeMsg[1] = "Pulse and direction";
  mTypeMsg[2] = "Quadrature";
}

DMIControl::~DMIControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void DMIControl::groupRead(const Group* group) {
  if (group->instanceOf<TimeTaggedDMIData>() == true) {
    const TimeTaggedDMIData& msg = group->typeCast<TimeTaggedDMIData>();
    mpUi->signedSpinBox->setValue(msg.mSignedDistanceTraveled);
    mpUi->unsignedSpinBox->setValue(msg.mUnsignedDistanceTraveled);
    mpUi->scaleSpinBox->setValue(msg.mDMIScaleFactor);
    mpUi->rateSpinBox->setValue(msg.mDMIDataRate);
    mpUi->statusText->setText(mStatusMsg[msg.mDataStatus].c_str());
    mpUi->typeText->setText(mTypeMsg[msg.mDMIType].c_str());
  }
}
