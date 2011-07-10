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

#include "visualization/StatusControl.h"

#include "visualization/ReadThread.h"
#include "types/GeneralStatusFDIR.h"
#include "ui_StatusControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

StatusControl::StatusControl() :
  mpUi(new Ui_StatusControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));
}

StatusControl::~StatusControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void StatusControl::groupRead(const Group* group) {
  if (group->instanceOf<GeneralStatusFDIR>() == true) {
    const GeneralStatusFDIR& msg = group->typeCast<GeneralStatusFDIR>();
    mpUi->statusASpinBox->setValue(msg.mGeneralStatusA);
    mpUi->statusBSpinBox->setValue(msg.mGeneralStatusB);
    mpUi->statusCSpinBox->setValue(msg.mGeneralStatusC);
    mpUi->fdir1StatusSpinBox->setValue(msg.mFDIRLevel1Status);
    mpUi->fdir1IMUSpinBox->setValue(msg.mFDIRLevel1Failures);
    mpUi->fdir2StatusSpinBox->setValue(msg.mFDIRLevel2Status);
    mpUi->fdir3StatusSpinBox->setValue(msg.mFDIRLevel3Status);
    mpUi->fdir4StatusSpinBox->setValue(msg.mFDIRLevel4Status);
    mpUi->fdir5StatusSpinBox->setValue(msg.mFDIRLevel5Status);
    mpUi->statusSpinBox->setValue(msg.mExtendedStatus);
  }
}
