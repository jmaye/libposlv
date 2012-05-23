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

#include <bitset>

#include "types/GeneralStatusFDIR.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_FDIRControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

FDIRControl::FDIRControl() :
    mUi(new Ui_FDIRControl()) {
  mUi->setupUi(this);
  mUi->imuPosErrorLed->setColor(Qt::red);
  mUi->imuStatusLed->setColor(Qt::red);
  mUi->imuFailureLed->setColor(Qt::red);
  mUi->iinConfLed->setColor(Qt::red);
  mUi->primGPSNotNavLed->setColor(Qt::red);
  mUi->primGPSNotAvLed->setColor(Qt::red);
  mUi->primDataGapLed->setColor(Qt::red);
  mUi->primGPSObsLed->setColor(Qt::red);
  mUi->primGPSTimeRecLed->setColor(Qt::red);
  mUi->primGPSPPSLed->setColor(Qt::red);
  mUi->primGPSSNRLed->setColor(Qt::red);
  mUi->baseGPSDataGapLed->setColor(Qt::red);
  mUi->baseGPSParityLed->setColor(Qt::red);
  mUi->baseGPSMsgRejectLed->setColor(Qt::red);
  mUi->secGPSDataGapLed->setColor(Qt::red);
  mUi->secGPSSNRLed->setColor(Qt::red);
  mUi->secGPSObsDataGapLed->setColor(Qt::red);
  mUi->secGPSExcessLockLed->setColor(Qt::red);
  mUi->gamsAmbLed->setColor(Qt::red);
  mUi->primGPSMissingLed->setColor(Qt::red);
  mUi->primGPSExcLockLed->setColor(Qt::red);
  mUi->primEphemLed->setColor(Qt::red);
  mUi->primGPSRejectedLed->setColor(Qt::red);
  mUi->primGPSOmniXPLed->setColor(Qt::red);
  mUi->excessPOSErrorLed->setColor(Qt::red);
  mUi->dmiRejectedLed->setColor(Qt::red);
  mUi->inertialMaxLed->setColor(Qt::red);
  mUi->excessPrimGPSClockLed->setColor(Qt::red);
  mUi->gamsRejectedLed->setColor(Qt::red);
  mUi->excGAMSOffsetLed->setColor(Qt::red);
  mUi->dmiSpeedMaxLed->setColor(Qt::red);
  mUi->yAccFailureLed->setColor(Qt::red);
  mUi->zGyroFailureLed->setColor(Qt::red);
  mUi->primGPSPosRejectedLed->setColor(Qt::red);
  mUi->xGyroFailureLed->setColor(Qt::red);
  mUi->excessPrimGPSErrorLed->setColor(Qt::red);
  mUi->primGPSOmniVBSLed->setColor(Qt::red);
  mUi->primGPSVelMaxLed->setColor(Qt::red);
  mUi->yGyroFailureLed->setColor(Qt::red);
  mUi->zAccFailureLed->setColor(Qt::red);
  mUi->xAccFailureLed->setColor(Qt::red);
  mUi->primGPSOmniHPLed->setColor(Qt::red);
  mUi->primGPSPosMaxLed->setColor(Qt::red);
  mUi->primGPSVelRejectedLed->setColor(Qt::red);
  mUi->primGPSPPPLed->setColor(Qt::red);
  mUi->dmiFailedLed->setColor(Qt::red);
  mUi->iinWLLed->setColor(Qt::red);
  mUi->iinNLLed->setColor(Qt::red);
}

FDIRControl::~FDIRControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void FDIRControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<GeneralStatusFDIR>()) {
      const GeneralStatusFDIR& msg = group.typeCast<GeneralStatusFDIR>();
      mUi->fdir1IMUSpinBox->setValue(msg.mFDIRLevel1Failures);
      std::bitset<32> fdir1(msg.mFDIRLevel1Status);
      std::bitset<16> fdir2(msg.mFDIRLevel2Status);
      std::bitset<16> fdir4(msg.mFDIRLevel4Status);
      std::bitset<16> fdir5(msg.mFDIRLevel5Status);
      std::bitset<32> extStatus(msg.mExtendedStatus);
      for (size_t i = 0; i < 32; i++) {
        switch (i) {
          case 0:
            if (fdir1.test(i))
              mUi->imuPosErrorLed->setColor(Qt::green);
            else
              mUi->imuPosErrorLed->setColor(Qt::red);
            break;
          case 1:
            if (fdir1.test(i))
              mUi->imuStatusLed->setColor(Qt::green);
            else
              mUi->imuStatusLed->setColor(Qt::red);
            break;
          case 2:
            if (fdir1.test(i))
              mUi->imuFailureLed->setColor(Qt::green);
            else
              mUi->imuFailureLed->setColor(Qt::red);
            break;
          case 3:
            if (fdir1.test(i))
              mUi->iinConfLed->setColor(Qt::green);
            else
              mUi->iinConfLed->setColor(Qt::red);
            break;
          case 5:
            if (fdir1.test(i))
              mUi->primGPSNotNavLed->setColor(Qt::green);
            else
              mUi->primGPSNotNavLed->setColor(Qt::red);
            break;
          case 6:
            if (fdir1.test(i))
              mUi->primGPSNotAvLed->setColor(Qt::green);
            else
              mUi->primGPSNotAvLed->setColor(Qt::red);
            break;
          case 7:
            if (fdir1.test(i))
              mUi->primDataGapLed->setColor(Qt::green);
            else
              mUi->primDataGapLed->setColor(Qt::red);
            break;
          case 8:
            if (fdir1.test(i))
              mUi->primGPSPPSLed->setColor(Qt::green);
            else
              mUi->primGPSPPSLed->setColor(Qt::red);
            break;
          case 9:
            if (fdir1.test(i))
              mUi->primGPSTimeRecLed->setColor(Qt::green);
            else
              mUi->primGPSTimeRecLed->setColor(Qt::red);
            break;
          case 10:
            if (fdir1.test(i))
              mUi->primGPSObsLed->setColor(Qt::green);
            else
              mUi->primGPSObsLed->setColor(Qt::red);
            break;
          case 11:
            if (fdir1.test(i))
              mUi->primEphemLed->setColor(Qt::green);
            else
              mUi->primEphemLed->setColor(Qt::red);
            break;
          case 12:
            if (fdir1.test(i))
              mUi->primGPSExcLockLed->setColor(Qt::green);
            else
              mUi->primGPSExcLockLed->setColor(Qt::red);
            break;
          case 13:
            if (fdir1.test(i))
              mUi->primGPSMissingLed->setColor(Qt::green);
            else
              mUi->primGPSMissingLed->setColor(Qt::red);
            break;
          case 16:
            if (fdir1.test(i))
              mUi->primGPSSNRLed->setColor(Qt::green);
            else
              mUi->primGPSSNRLed->setColor(Qt::red);
            break;
          case 17:
            if (fdir1.test(i))
              mUi->baseGPSDataGapLed->setColor(Qt::green);
            else
              mUi->baseGPSDataGapLed->setColor(Qt::red);
            break;
          case 18:
            if (fdir1.test(i))
              mUi->baseGPSParityLed->setColor(Qt::green);
            else
              mUi->baseGPSParityLed->setColor(Qt::red);
            break;
          case 19:
            if (fdir1.test(i))
              mUi->baseGPSMsgRejectLed->setColor(Qt::green);
            else
              mUi->baseGPSMsgRejectLed->setColor(Qt::red);
            break;
          case 20:
            if (fdir1.test(i))
              mUi->secGPSDataGapLed->setColor(Qt::green);
            else
              mUi->secGPSDataGapLed->setColor(Qt::red);
            break;
          case 21:
            if (fdir1.test(i))
              mUi->secGPSObsDataGapLed->setColor(Qt::green);
            else
              mUi->secGPSObsDataGapLed->setColor(Qt::red);
            break;
          case 22:
            if (fdir1.test(i))
              mUi->secGPSSNRLed->setColor(Qt::green);
            else
              mUi->secGPSSNRLed->setColor(Qt::red);
            break;
          case 23:
            if (fdir1.test(i))
              mUi->secGPSExcessLockLed->setColor(Qt::green);
            else
              mUi->secGPSExcessLockLed->setColor(Qt::red);
            break;
          case 26:
            if (fdir1.test(i))
              mUi->gamsAmbLed->setColor(Qt::green);
            else
              mUi->gamsAmbLed->setColor(Qt::red);
            break;
          case 28:
            if (fdir1.test(i))
              mUi->dmiFailedLed->setColor(Qt::green);
            else
              mUi->dmiFailedLed->setColor(Qt::red);
            break;
          case 30:
            if (fdir1.test(i))
              mUi->iinWLLed->setColor(Qt::green);
            else
              mUi->iinWLLed->setColor(Qt::red);
            break;
          case 31:
            if (fdir1.test(i))
              mUi->iinNLLed->setColor(Qt::green);
            else
              mUi->iinNLLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
      for (size_t i = 0; i < 16; i++) {
        switch (i) {
          case 0:
            if (fdir2.test(i))
              mUi->inertialMaxLed->setColor(Qt::green);
            else
              mUi->inertialMaxLed->setColor(Qt::red);
            break;
          case 1:
            if (fdir2.test(i))
              mUi->primGPSVelMaxLed->setColor(Qt::green);
            else
              mUi->primGPSVelMaxLed->setColor(Qt::red);
            break;
          case 2:
            if (fdir2.test(i))
              mUi->primGPSPosMaxLed->setColor(Qt::green);
            else
              mUi->primGPSPosMaxLed->setColor(Qt::red);
            break;
          case 4:
            if (fdir2.test(i))
              mUi->dmiSpeedMaxLed->setColor(Qt::green);
            else
              mUi->dmiSpeedMaxLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
      for (size_t i = 0; i < 16; i++) {
        switch (i) {
          case 0:
            if (fdir4.test(i))
              mUi->primGPSPosRejectedLed->setColor(Qt::green);
            else
              mUi->primGPSPosRejectedLed->setColor(Qt::red);
            break;
          case 1:
            if (fdir4.test(i))
              mUi->primGPSVelRejectedLed->setColor(Qt::green);
            else
              mUi->primGPSVelRejectedLed->setColor(Qt::red);
            break;
          case 2:
            if (fdir4.test(i))
              mUi->gamsRejectedLed->setColor(Qt::green);
            else
              mUi->gamsRejectedLed->setColor(Qt::red);
            break;
          case 4:
            if (fdir4.test(i))
              mUi->dmiRejectedLed->setColor(Qt::green);
            else
              mUi->dmiRejectedLed->setColor(Qt::red);
            break;
          case 5:
            if (fdir4.test(i))
              mUi->primGPSRejectedLed->setColor(Qt::green);
            else
              mUi->primGPSRejectedLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
      for (size_t i = 0; i < 16; i++) {
        switch (i) {
          case 0:
            if (fdir5.test(i))
              mUi->xAccFailureLed->setColor(Qt::green);
            else
              mUi->xAccFailureLed->setColor(Qt::red);
            break;
          case 1:
            if (fdir5.test(i))
              mUi->yAccFailureLed->setColor(Qt::green);
            else
              mUi->yAccFailureLed->setColor(Qt::red);
            break;
          case 2:
            if (fdir5.test(i))
              mUi->zAccFailureLed->setColor(Qt::green);
            else
              mUi->zAccFailureLed->setColor(Qt::red);
            break;
          case 3:
            if (fdir5.test(i))
              mUi->xGyroFailureLed->setColor(Qt::green);
            else
              mUi->xGyroFailureLed->setColor(Qt::red);
            break;
          case 4:
            if (fdir5.test(i))
              mUi->yGyroFailureLed->setColor(Qt::green);
            else
              mUi->yGyroFailureLed->setColor(Qt::red);
            break;
          case 5:
            if (fdir5.test(i))
              mUi->zGyroFailureLed->setColor(Qt::green);
            else
              mUi->zGyroFailureLed->setColor(Qt::red);
            break;
          case 6:
            if (fdir5.test(i))
              mUi->excGAMSOffsetLed->setColor(Qt::green);
            else
              mUi->excGAMSOffsetLed->setColor(Qt::red);
            break;
          case 7:
            if (fdir5.test(i))
              mUi->excessPrimGPSErrorLed->setColor(Qt::green);
            else
              mUi->excessPrimGPSErrorLed->setColor(Qt::red);
            break;
          case 10:
            if (fdir5.test(i))
              mUi->excessPOSErrorLed->setColor(Qt::green);
            else
              mUi->excessPOSErrorLed->setColor(Qt::red);
            break;
          case 11:
            if (fdir5.test(i))
              mUi->excessPrimGPSClockLed->setColor(Qt::green);
            else
              mUi->excessPrimGPSClockLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
      for (size_t i = 0; i < 32; i++) {
        switch (i) {
          case 0:
            if (extStatus.test(i))
              mUi->primGPSOmniHPLed->setColor(Qt::green);
            else
              mUi->primGPSOmniHPLed->setColor(Qt::red);
            break;
          case 1:
            if (extStatus.test(i))
              mUi->primGPSOmniXPLed->setColor(Qt::green);
            else
              mUi->primGPSOmniXPLed->setColor(Qt::red);
            break;
          case 2:
            if (extStatus.test(i))
              mUi->primGPSOmniVBSLed->setColor(Qt::green);
            else
              mUi->primGPSOmniVBSLed->setColor(Qt::red);
            break;
          case 3:
            if (extStatus.test(i))
              mUi->primGPSPPPLed->setColor(Qt::green);
            else
              mUi->primGPSPPPLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
    }
  }
}
