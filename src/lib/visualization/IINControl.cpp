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

#include "visualization/IINControl.h"

#include "visualization/ReadThread.h"
#include "types/IINSolutionStatus.h"
#include "ui_IINControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IINControl::IINControl() :
  mpUi(new Ui_IINControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[1] = "Fixed narrow lane RTK";
  mStatusMsg[2] = "Fixed wide lane RTK";
  mStatusMsg[3] = "Float RTK";
  mStatusMsg[4] = "Code DGPS";
  mStatusMsg[5] = "RTCM DGPS";
  mStatusMsg[6] = "Autonmous (C/A)";
  mStatusMsg[7] = "GPS navigation solution";
  mStatusMsg[8] = "No solution";
}

IINControl::~IINControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void IINControl::groupRead(const Group* group) {
  if (group->instanceOf<IINSolutionStatus>() == true) {
    const IINSolutionStatus& msg = group->typeCast<IINSolutionStatus>();
    mpUi->satIINSpinBox->setValue(msg.mNumberOfSatellites);
    mpUi->statusText->setText(mStatusMsg[msg.mIINProcessingStatus].c_str());
    mpUi->baselineSpinBox->setValue(msg.mBaselineLength);
    mpUi->pdopSpinBox->setValue(msg.mAPrioriPDOP);
  }
}
