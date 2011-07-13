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

#include "visualization/FDIRControl.h"

#include "visualization/ReadThread.h"
#include "types/GeneralStatusFDIR.h"
#include "ui_FDIRControl.h"

#include <bitset>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

FDIRControl::FDIRControl() :
  mpUi(new Ui_FDIRControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mpUi->imuPosErrorLed->setColor(Qt::red);
  mpUi->imuStatusLed->setColor(Qt::red);
  mpUi->imuFailureLed->setColor(Qt::red);
  mpUi->iinConfLed->setColor(Qt::red);
  mpUi->primGPSNotNavLed->setColor(Qt::red);
  mpUi->primGPSNotAvLed->setColor(Qt::red);
  mpUi->primDataGapLed->setColor(Qt::red);
  mpUi->primGPSObsLed->setColor(Qt::red);
  mpUi->primGPSTimeRecLed->setColor(Qt::red);
  mpUi->primGPSPPSLed->setColor(Qt::red);
  mpUi->primGPSSNRLed->setColor(Qt::red);
  mpUi->baseGPSDataGapLed->setColor(Qt::red);
  mpUi->baseGPSParityLed->setColor(Qt::red);
  mpUi->baseGPSMsgRejectLed->setColor(Qt::red);
  mpUi->secGPSDataGapLed->setColor(Qt::red);
  mpUi->secGPSSNRLed->setColor(Qt::red);
  mpUi->secGPSObsDataGapLed->setColor(Qt::red);
  mpUi->secGPSExcessLockLed->setColor(Qt::red);
  mpUi->gamsAmbLed->setColor(Qt::red);
  mpUi->primGPSMissingLed->setColor(Qt::red);
  mpUi->primGPSExcLockLed->setColor(Qt::red);
  mpUi->primEphemLed->setColor(Qt::red);
  mpUi->primGPSRejectedLed->setColor(Qt::red);
  mpUi->primGPSOmniXPLed->setColor(Qt::red);
  mpUi->excessPOSErrorLed->setColor(Qt::red);
  mpUi->dmiRejectedLed->setColor(Qt::red);
  mpUi->inertialMaxLed->setColor(Qt::red);
  mpUi->excessPrimGPSClockLed->setColor(Qt::red);
  mpUi->gamsRejectedLed->setColor(Qt::red);
  mpUi->excGAMSOffsetLed->setColor(Qt::red);
  mpUi->dmiSpeedMaxLed->setColor(Qt::red);
  mpUi->yAccFailureLed->setColor(Qt::red);
  mpUi->zGyroFailureLed->setColor(Qt::red);
  mpUi->primGPSPosRejectedLed->setColor(Qt::red);
  mpUi->xGyroFailureLed->setColor(Qt::red);
  mpUi->excessPrimGPSErrorLed->setColor(Qt::red);
  mpUi->primGPSOmniVBSLed->setColor(Qt::red);
  mpUi->primGPSVelMaxLed->setColor(Qt::red);
  mpUi->yGyroFailureLed->setColor(Qt::red);
  mpUi->zAccFailureLed->setColor(Qt::red);
  mpUi->xAccFailureLed->setColor(Qt::red);
  mpUi->primGPSOmniHPLed->setColor(Qt::red);
  mpUi->primGPSPosMaxLed->setColor(Qt::red);
  mpUi->primGPSVelRejectedLed->setColor(Qt::red);
  mpUi->primGPSPPPLed->setColor(Qt::red);
  mpUi->dmiFailedLed->setColor(Qt::red);
  mpUi->iinWLLed->setColor(Qt::red);
  mpUi->iinNLLed->setColor(Qt::red);
}

FDIRControl::~FDIRControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void FDIRControl::groupRead(const Group* group) {
  if (group->instanceOf<GeneralStatusFDIR>() == true) {
    const GeneralStatusFDIR& msg = group->typeCast<GeneralStatusFDIR>();
    mpUi->fdir1IMUSpinBox->setValue(msg.mFDIRLevel1Failures);

    std::bitset<32> fdir1(msg.mFDIRLevel1Status);
    std::bitset<16> fdir2(msg.mFDIRLevel2Status);
    std::bitset<16> fdir4(msg.mFDIRLevel4Status);
    std::bitset<16> fdir5(msg.mFDIRLevel5Status);
    std::bitset<32> extStatus(msg.mExtendedStatus);

    for (size_t i = 0; i < 32; i++) {
      switch (i) {
        case 0:
          if (fdir1.test(i))
            mpUi->imuPosErrorLed->setColor(Qt::green);
          else
            mpUi->imuPosErrorLed->setColor(Qt::red);
          break;
        case 1:
          if (fdir1.test(i))
            mpUi->imuStatusLed->setColor(Qt::green);
          else
            mpUi->imuStatusLed->setColor(Qt::red);
          break;
        case 2:
          if (fdir1.test(i))
            mpUi->imuFailureLed->setColor(Qt::green);
          else
            mpUi->imuFailureLed->setColor(Qt::red);
          break;
        case 3:
          if (fdir1.test(i))
            mpUi->iinConfLed->setColor(Qt::green);
          else
            mpUi->iinConfLed->setColor(Qt::red);
          break;
        case 5:
          if (fdir1.test(i))
            mpUi->primGPSNotNavLed->setColor(Qt::green);
          else
            mpUi->primGPSNotNavLed->setColor(Qt::red);
          break;
        case 6:
          if (fdir1.test(i))
            mpUi->primGPSNotAvLed->setColor(Qt::green);
          else
            mpUi->primGPSNotAvLed->setColor(Qt::red);
          break;
        case 7:
          if (fdir1.test(i))
            mpUi->primDataGapLed->setColor(Qt::green);
          else
            mpUi->primDataGapLed->setColor(Qt::red);
          break;
        case 8:
          if (fdir1.test(i))
            mpUi->primGPSPPSLed->setColor(Qt::green);
          else
            mpUi->primGPSPPSLed->setColor(Qt::red);
          break;
        case 9:
          if (fdir1.test(i))
            mpUi->primGPSTimeRecLed->setColor(Qt::green);
          else
            mpUi->primGPSTimeRecLed->setColor(Qt::red);
          break;
        case 10:
          if (fdir1.test(i))
            mpUi->primGPSObsLed->setColor(Qt::green);
          else
            mpUi->primGPSObsLed->setColor(Qt::red);
          break;
        case 11:
          if (fdir1.test(i))
            mpUi->primEphemLed->setColor(Qt::green);
          else
            mpUi->primEphemLed->setColor(Qt::red);
          break;
        case 12:
          if (fdir1.test(i))
            mpUi->primGPSExcLockLed->setColor(Qt::green);
          else
            mpUi->primGPSExcLockLed->setColor(Qt::red);
          break;
        case 13:
          if (fdir1.test(i))
            mpUi->primGPSMissingLed->setColor(Qt::green);
          else
            mpUi->primGPSMissingLed->setColor(Qt::red);
          break;
        case 16:
          if (fdir1.test(i))
            mpUi->primGPSSNRLed->setColor(Qt::green);
          else
            mpUi->primGPSSNRLed->setColor(Qt::red);
          break;
        case 17:
          if (fdir1.test(i))
            mpUi->baseGPSDataGapLed->setColor(Qt::green);
          else
            mpUi->baseGPSDataGapLed->setColor(Qt::red);
          break;
        case 18:
          if (fdir1.test(i))
            mpUi->baseGPSParityLed->setColor(Qt::green);
          else
            mpUi->baseGPSParityLed->setColor(Qt::red);
          break;
        case 19:
          if (fdir1.test(i))
            mpUi->baseGPSMsgRejectLed->setColor(Qt::green);
          else
            mpUi->baseGPSMsgRejectLed->setColor(Qt::red);
          break;
        case 20:
          if (fdir1.test(i))
            mpUi->secGPSDataGapLed->setColor(Qt::green);
          else
            mpUi->secGPSDataGapLed->setColor(Qt::red);
          break;
        case 21:
          if (fdir1.test(i))
            mpUi->secGPSObsDataGapLed->setColor(Qt::green);
          else
            mpUi->secGPSObsDataGapLed->setColor(Qt::red);
          break;
        case 22:
          if (fdir1.test(i))
            mpUi->secGPSSNRLed->setColor(Qt::green);
          else
            mpUi->secGPSSNRLed->setColor(Qt::red);
          break;
        case 23:
          if (fdir1.test(i))
            mpUi->secGPSExcessLockLed->setColor(Qt::green);
          else
            mpUi->secGPSExcessLockLed->setColor(Qt::red);
          break;
        case 26:
          if (fdir1.test(i))
            mpUi->gamsAmbLed->setColor(Qt::green);
          else
            mpUi->gamsAmbLed->setColor(Qt::red);
          break;
        case 28:
          if (fdir1.test(i))
            mpUi->dmiFailedLed->setColor(Qt::green);
          else
            mpUi->dmiFailedLed->setColor(Qt::red);
          break;
        case 30:
          if (fdir1.test(i))
            mpUi->iinWLLed->setColor(Qt::green);
          else
            mpUi->iinWLLed->setColor(Qt::red);
          break;
        case 31:
          if (fdir1.test(i))
            mpUi->iinNLLed->setColor(Qt::green);
          else
            mpUi->iinNLLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

    for (size_t i = 0; i < 16; i++) {
      switch (i) {
        case 0:
          if (fdir2.test(i))
            mpUi->inertialMaxLed->setColor(Qt::green);
          else
            mpUi->inertialMaxLed->setColor(Qt::red);
          break;
        case 1:
          if (fdir2.test(i))
            mpUi->primGPSVelMaxLed->setColor(Qt::green);
          else
            mpUi->primGPSVelMaxLed->setColor(Qt::red);
          break;
        case 2:
          if (fdir2.test(i))
            mpUi->primGPSPosMaxLed->setColor(Qt::green);
          else
            mpUi->primGPSPosMaxLed->setColor(Qt::red);
          break;
        case 4:
          if (fdir2.test(i))
            mpUi->dmiSpeedMaxLed->setColor(Qt::green);
          else
            mpUi->dmiSpeedMaxLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

    for (size_t i = 0; i < 16; i++) {
      switch (i) {
        case 0:
          if (fdir4.test(i))
            mpUi->primGPSPosRejectedLed->setColor(Qt::green);
          else
            mpUi->primGPSPosRejectedLed->setColor(Qt::red);
          break;
        case 1:
          if (fdir4.test(i))
            mpUi->primGPSVelRejectedLed->setColor(Qt::green);
          else
            mpUi->primGPSVelRejectedLed->setColor(Qt::red);
          break;
        case 2:
          if (fdir4.test(i))
            mpUi->gamsRejectedLed->setColor(Qt::green);
          else
            mpUi->gamsRejectedLed->setColor(Qt::red);
          break;
        case 4:
          if (fdir4.test(i))
            mpUi->dmiRejectedLed->setColor(Qt::green);
          else
            mpUi->dmiRejectedLed->setColor(Qt::red);
          break;
        case 5:
          if (fdir4.test(i))
            mpUi->primGPSRejectedLed->setColor(Qt::green);
          else
            mpUi->primGPSRejectedLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

    for (size_t i = 0; i < 16; i++) {
      switch (i) {
        case 0:
          if (fdir5.test(i))
            mpUi->xAccFailureLed->setColor(Qt::green);
          else
            mpUi->xAccFailureLed->setColor(Qt::red);
          break;
        case 1:
          if (fdir5.test(i))
            mpUi->yAccFailureLed->setColor(Qt::green);
          else
            mpUi->yAccFailureLed->setColor(Qt::red);
          break;
        case 2:
          if (fdir5.test(i))
            mpUi->zAccFailureLed->setColor(Qt::green);
          else
            mpUi->zAccFailureLed->setColor(Qt::red);
          break;
        case 3:
          if (fdir5.test(i))
            mpUi->xGyroFailureLed->setColor(Qt::green);
          else
            mpUi->xGyroFailureLed->setColor(Qt::red);
          break;
        case 4:
          if (fdir5.test(i))
            mpUi->yGyroFailureLed->setColor(Qt::green);
          else
            mpUi->yGyroFailureLed->setColor(Qt::red);
          break;
        case 5:
          if (fdir5.test(i))
            mpUi->zGyroFailureLed->setColor(Qt::green);
          else
            mpUi->zGyroFailureLed->setColor(Qt::red);
          break;
        case 6:
          if (fdir5.test(i))
            mpUi->excGAMSOffsetLed->setColor(Qt::green);
          else
            mpUi->excGAMSOffsetLed->setColor(Qt::red);
          break;
        case 7:
          if (fdir5.test(i))
            mpUi->excessPrimGPSErrorLed->setColor(Qt::green);
          else
            mpUi->excessPrimGPSErrorLed->setColor(Qt::red);
          break;
        case 10:
          if (fdir5.test(i))
            mpUi->excessPOSErrorLed->setColor(Qt::green);
          else
            mpUi->excessPOSErrorLed->setColor(Qt::red);
          break;
        case 11:
          if (fdir5.test(i))
            mpUi->excessPrimGPSClockLed->setColor(Qt::green);
          else
            mpUi->excessPrimGPSClockLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

    for (size_t i = 0; i < 32; i++) {
      switch (i) {
        case 0:
          if (extStatus.test(i))
            mpUi->primGPSOmniHPLed->setColor(Qt::green);
          else
            mpUi->primGPSOmniHPLed->setColor(Qt::red);
          break;
        case 1:
          if (extStatus.test(i))
            mpUi->primGPSOmniXPLed->setColor(Qt::green);
          else
            mpUi->primGPSOmniXPLed->setColor(Qt::red);
          break;
        case 2:
          if (extStatus.test(i))
            mpUi->primGPSOmniVBSLed->setColor(Qt::green);
          else
            mpUi->primGPSOmniVBSLed->setColor(Qt::red);
          break;
        case 3:
          if (extStatus.test(i))
            mpUi->primGPSPPPLed->setColor(Qt::green);
          else
            mpUi->primGPSPPPLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

  }
}
