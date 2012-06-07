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

#include "visualization/GeneralStatusTab.h"

#include <bitset>

#include "types/GeneralStatusFDIR.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_GeneralStatusTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeneralStatusTab::GeneralStatusTab() :
    mUi(new Ui_GeneralStatusTab()) {
  mUi->setupUi(this);
  mUi->coarseLevelingActiveLed->setColor(Qt::red);
  mUi->coarseLevelingFailedLed->setColor(Qt::red);
  mUi->quadrantResolvedLed->setColor(Qt::red);
  mUi->fineAlignActiveLed->setColor(Qt::red);
  mUi->inertialNavInitLed->setColor(Qt::red);
  mUi->inertialNavAlignActiveLed->setColor(Qt::red);
  mUi->degNavSolLed->setColor(Qt::red);
  mUi->refPrimGPSLed->setColor(Qt::red);
  mUi->initPosValidLed->setColor(Qt::red);
  mUi->fullNavSolLed->setColor(Qt::red);
  mUi->logPortFileOpenLed->setColor(Qt::red);
  mUi->logPortLogEnableLed->setColor(Qt::red);
  mUi->LogPortDeviceFullLed->setColor(Qt::red);
  mUi->ramConfigLed->setColor(Qt::red);
  mUi->nvmWriteSuccessLed->setColor(Qt::red);
  mUi->nvmReadFailLed->setColor(Qt::red);
  mUi->nvmWriteFailLed->setColor(Qt::red);
  mUi->cpuLoading55Led->setColor(Qt::red);
  mUi->cpuLoading85Led->setColor(Qt::red);
  mUi->logPortWriteErrorLed->setColor(Qt::red);
  mUi->refSensor2Led->setColor(Qt::red);
  mUi->refSensor1Led->setColor(Qt::red);
  mUi->gamsInstallParamsLed->setColor(Qt::red);
  mUi->primGPSRTKModeLed->setColor(Qt::red);
  mUi->primGPSNotConfiguredLed->setColor(Qt::red);
  mUi->gamsCalibReqLed->setColor(Qt::red);
  mUi->attitudeRMSLed->setColor(Qt::red);
  mUi->primGPSCAModeLed->setColor(Qt::red);
  mUi->gamsCalibFailedLed->setColor(Qt::red);
  mUi->primGPSResetLed->setColor(Qt::red);
  mUi->velRMSLed->setColor(Qt::red);
  mUi->gamsSolOkLed->setColor(Qt::red);
  mUi->primGPSInitFailedLed->setColor(Qt::red);
  mUi->gamsCalibProgressLed->setColor(Qt::red);
  mUi->gamsCalibForcedLed->setColor(Qt::red);
  mUi->primGPSConfigSentLed->setColor(Qt::red);
  mUi->primGPSWideRTKModeLed->setColor(Qt::red);
  mUi->headingRMSLed->setColor(Qt::red);
  mUi->primGPSNavSolInUseLed->setColor(Qt::red);
  mUi->gamsCalibSuspLed->setColor(Qt::red);
  mUi->gamsSolInUseLed->setColor(Qt::red);
  mUi->primGPSDIffModLed->setColor(Qt::red);
  mUi->posRMSLed->setColor(Qt::red);
  mUi->gamsCalibCompleteLed->setColor(Qt::red);
  mUi->primGPSNarrowRTKModeLed->setColor(Qt::red);
  mUi->secGPSObsLed->setColor(Qt::red);
  mUi->primGPSObsLed->setColor(Qt::red);
  mUi->primGPSPCodeLed->setColor(Qt::red);
  mUi->cmrRTKMsgInUseLed->setColor(Qt::red);
  mUi->iinDGPSLed->setColor(Qt::red);
  mUi->iinDRModeLed->setColor(Qt::red);
  mUi->iinRTCMDGPSLed->setColor(Qt::red);
  mUi->recRTCM18Led->setColor(Qt::red);
  mUi->zupdProcEnabledLed->setColor(Qt::red);
  mUi->iinNarrowRTKLed->setColor(Qt::red);
  mUi->iinWideRTKLed->setColor(Qt::red);
  mUi->iinCALed->setColor(Qt::red);
  mUi->rtcmRTKMsgInUseLed->setColor(Qt::red);
  mUi->recCMR94Led->setColor(Qt::red);;
  mUi->rtcmDiffCorrLed->setColor(Qt::red);
  mUi->dmiInUseLed->setColor(Qt::red);
  mUi->iinRTKLed->setColor(Qt::red);
  mUi->recCMR0Led->setColor(Qt::red);
  mUi->recRTCM19Led->setColor(Qt::red);
  mUi->posFixInUseLed->setColor(Qt::red);
  mUi->zupdInUseLed->setColor(Qt::red);
  mUi->recCMR1Led->setColor(Qt::red);
  mUi->recRTCM1Led->setColor(Qt::red);
  mUi->iinGPSLed->setColor(Qt::red);
  mUi->recCMR2Led->setColor(Qt::red);
  mUi->recRTCM9Led->setColor(Qt::red);
  mUi->recRTCM3Led->setColor(Qt::red);
}

GeneralStatusTab::~GeneralStatusTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GeneralStatusTab::readPacket(std::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<GeneralStatusFDIR>()) {
      const GeneralStatusFDIR& msg = group.typeCast<GeneralStatusFDIR>();
      std::bitset<32> statusA(msg.mGeneralStatusA);
      std::bitset<32> statusB(msg.mGeneralStatusB);
      std::bitset<32> statusC(msg.mGeneralStatusC);
      for (size_t i = 0; i < 32; i++) {
        switch (i) {
          case 0:
            if (statusA.test(i))
              mUi->coarseLevelingActiveLed->setColor(Qt::green);
            else
              mUi->coarseLevelingActiveLed->setColor(Qt::red);
            break;
          case 1:
            if (statusA.test(i))
              mUi->coarseLevelingFailedLed->setColor(Qt::green);
            else
              mUi->coarseLevelingFailedLed->setColor(Qt::red);
            break;
          case 2:
            if (statusA.test(i))
              mUi->quadrantResolvedLed->setColor(Qt::green);
            else
              mUi->quadrantResolvedLed->setColor(Qt::red);
            break;
          case 3:
            if (statusA.test(i))
              mUi->fineAlignActiveLed->setColor(Qt::green);
            else
              mUi->fineAlignActiveLed->setColor(Qt::red);
            break;
          case 4:
            if (statusA.test(i))
              mUi->inertialNavInitLed->setColor(Qt::green);
            else
              mUi->inertialNavInitLed->setColor(Qt::red);
            break;
          case 5:
            if (statusA.test(i))
              mUi->inertialNavAlignActiveLed->setColor(Qt::green);
            else
              mUi->inertialNavAlignActiveLed->setColor(Qt::red);
            break;
          case 6:
            if (statusA.test(i))
              mUi->degNavSolLed->setColor(Qt::green);
            else
              mUi->degNavSolLed->setColor(Qt::red);
            break;
          case 7:
            if (statusA.test(i))
              mUi->fullNavSolLed->setColor(Qt::green);
            else
              mUi->fullNavSolLed->setColor(Qt::red);
            break;
          case 8:
            if (statusA.test(i))
              mUi->initPosValidLed->setColor(Qt::green);
            else
              mUi->initPosValidLed->setColor(Qt::red);
            break;
          case 9:
            if (statusA.test(i))
              mUi->refPrimGPSLed->setColor(Qt::green);
            else
              mUi->refPrimGPSLed->setColor(Qt::red);
            break;
          case 10:
            if (statusA.test(i))
              mUi->refSensor1Led->setColor(Qt::green);
            else
              mUi->refSensor1Led->setColor(Qt::red);
            break;
          case 11:
            if (statusA.test(i))
              mUi->refSensor2Led->setColor(Qt::green);
            else
              mUi->refSensor2Led->setColor(Qt::red);
            break;
          case 12:
            if (statusA.test(i))
              mUi->logPortWriteErrorLed->setColor(Qt::green);
            else
              mUi->logPortWriteErrorLed->setColor(Qt::red);
            break;
          case 13:
            if (statusA.test(i))
              mUi->logPortFileOpenLed->setColor(Qt::green);
            else
              mUi->logPortFileOpenLed->setColor(Qt::red);
            break;
          case 14:
            if (statusA.test(i))
              mUi->logPortLogEnableLed->setColor(Qt::green);
            else
              mUi->logPortLogEnableLed->setColor(Qt::red);
            break;
          case 15:
            if (statusA.test(i))
              mUi->LogPortDeviceFullLed->setColor(Qt::green);
            else
              mUi->LogPortDeviceFullLed->setColor(Qt::red);
            break;
          case 16:
            if (statusA.test(i))
              mUi->ramConfigLed->setColor(Qt::green);
            else
              mUi->ramConfigLed->setColor(Qt::red);
            break;
          case 17:
            if (statusA.test(i))
              mUi->nvmWriteSuccessLed->setColor(Qt::green);
            else
              mUi->nvmWriteSuccessLed->setColor(Qt::red);
            break;
          case 18:
            if (statusA.test(i))
              mUi->nvmWriteFailLed->setColor(Qt::green);
            else
              mUi->nvmWriteFailLed->setColor(Qt::red);
            break;
          case 19:
            if (statusA.test(i))
              mUi->nvmReadFailLed->setColor(Qt::green);
            else
              mUi->nvmReadFailLed->setColor(Qt::red);
            break;
          case 20:
            if (statusA.test(i))
              mUi->cpuLoading55Led->setColor(Qt::green);
            else
              mUi->cpuLoading55Led->setColor(Qt::red);
            break;
          case 21:
            if (statusA.test(i))
              mUi->cpuLoading85Led->setColor(Qt::green);
            else
              mUi->cpuLoading85Led->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
      for (size_t i = 0; i < 32; i++) {
        switch (i) {
          case 0:
            if (statusB.test(i))
              mUi->attitudeRMSLed->setColor(Qt::green);
            else
              mUi->attitudeRMSLed->setColor(Qt::red);
            break;
          case 1:
            if (statusB.test(i))
              mUi->headingRMSLed->setColor(Qt::green);
            else
              mUi->headingRMSLed->setColor(Qt::red);
            break;
          case 2:
            if (statusB.test(i))
              mUi->posRMSLed->setColor(Qt::green);
            else
              mUi->posRMSLed->setColor(Qt::red);
            break;
          case 3:
            if (statusB.test(i))
              mUi->velRMSLed->setColor(Qt::green);
            else
              mUi->velRMSLed->setColor(Qt::red);
            break;
          case 4:
            if (statusB.test(i))
              mUi->gamsCalibProgressLed->setColor(Qt::green);
            else
              mUi->gamsCalibProgressLed->setColor(Qt::red);
            break;
          case 5:
            if (statusB.test(i))
              mUi->gamsCalibCompleteLed->setColor(Qt::green);
            else
              mUi->gamsCalibCompleteLed->setColor(Qt::red);
            break;
          case 6:
            if (statusB.test(i))
              mUi->gamsCalibFailedLed->setColor(Qt::green);
            else
              mUi->gamsCalibFailedLed->setColor(Qt::red);
            break;
          case 7:
            if (statusB.test(i))
              mUi->gamsCalibReqLed->setColor(Qt::green);
            else
              mUi->gamsCalibReqLed->setColor(Qt::red);
            break;
          case 8:
            if (statusB.test(i))
              mUi->gamsInstallParamsLed->setColor(Qt::green);
            else
              mUi->gamsInstallParamsLed->setColor(Qt::red);
            break;
          case 9:
            if (statusB.test(i))
              mUi->gamsSolInUseLed->setColor(Qt::green);
            else
              mUi->gamsSolInUseLed->setColor(Qt::red);
            break;
          case 10:
            if (statusB.test(i))
              mUi->gamsSolOkLed->setColor(Qt::green);
            else
              mUi->gamsSolOkLed->setColor(Qt::red);
            break;
          case 11:
            if (statusB.test(i))
              mUi->gamsCalibSuspLed->setColor(Qt::green);
            else
              mUi->gamsCalibSuspLed->setColor(Qt::red);
            break;
          case 12:
            if (statusB.test(i))
              mUi->gamsCalibForcedLed->setColor(Qt::green);
            else
              mUi->gamsCalibForcedLed->setColor(Qt::red);
            break;
          case 13:
            if (statusB.test(i))
              mUi->primGPSNavSolInUseLed->setColor(Qt::green);
            else
              mUi->primGPSNavSolInUseLed->setColor(Qt::red);
            break;
          case 14:
            if (statusB.test(i))
              mUi->primGPSInitFailedLed->setColor(Qt::green);
            else
              mUi->primGPSInitFailedLed->setColor(Qt::red);
            break;
          case 15:
            if (statusB.test(i))
              mUi->primGPSResetLed->setColor(Qt::green);
            else
              mUi->primGPSResetLed->setColor(Qt::red);
            break;
          case 16:
            if (statusB.test(i))
              mUi->primGPSConfigSentLed->setColor(Qt::green);
            else
              mUi->primGPSConfigSentLed->setColor(Qt::red);
            break;
          case 17:
            if (statusB.test(i))
              mUi->primGPSNotConfiguredLed->setColor(Qt::green);
            else
              mUi->primGPSNotConfiguredLed->setColor(Qt::red);
            break;
          case 18:
            if (statusB.test(i))
              mUi->primGPSCAModeLed->setColor(Qt::green);
            else
              mUi->primGPSCAModeLed->setColor(Qt::red);
            break;
          case 19:
            if (statusB.test(i))
              mUi->primGPSDIffModLed->setColor(Qt::green);
            else
              mUi->primGPSDIffModLed->setColor(Qt::red);
            break;
          case 20:
            if (statusB.test(i))
              mUi->primGPSRTKModeLed->setColor(Qt::green);
            else
              mUi->primGPSRTKModeLed->setColor(Qt::red);
            break;
          case 21:
            if (statusB.test(i))
              mUi->primGPSWideRTKModeLed->setColor(Qt::green);
            else
              mUi->primGPSWideRTKModeLed->setColor(Qt::red);
            break;
          case 22:
            if (statusB.test(i))
              mUi->primGPSNarrowRTKModeLed->setColor(Qt::green);
            else
              mUi->primGPSNarrowRTKModeLed->setColor(Qt::red);
            break;
          case 23:
            if (statusB.test(i))
              mUi->primGPSObsLed->setColor(Qt::green);
            else
              mUi->primGPSObsLed->setColor(Qt::red);
            break;
          case 24:
            if (statusB.test(i))
              mUi->secGPSObsLed->setColor(Qt::green);
            else
              mUi->secGPSObsLed->setColor(Qt::red);
            break;
          case 31:
            if (statusB.test(i))
              mUi->primGPSPCodeLed->setColor(Qt::green);
            else
              mUi->primGPSPCodeLed->setColor(Qt::red);
            break;
        }
      }
      for (size_t i = 0; i < 32; i++) {
        switch (i) {
          case 2:
            if (statusC.test(i))
              mUi->dmiInUseLed->setColor(Qt::green);
            else
              mUi->dmiInUseLed->setColor(Qt::red);
            break;
          case 3:
            if (statusC.test(i))
              mUi->zupdProcEnabledLed->setColor(Qt::green);
            else
              mUi->zupdProcEnabledLed->setColor(Qt::red);
            break;
          case 4:
            if (statusC.test(i))
              mUi->zupdInUseLed->setColor(Qt::green);
            else
              mUi->zupdInUseLed->setColor(Qt::red);
            break;
          case 5:
            if (statusC.test(i))
              mUi->posFixInUseLed->setColor(Qt::green);
            else
              mUi->posFixInUseLed->setColor(Qt::red);
            break;
          case 6:
            if (statusC.test(i))
              mUi->rtcmDiffCorrLed->setColor(Qt::green);
            else
              mUi->rtcmDiffCorrLed->setColor(Qt::red);
            break;
          case 7:
            if (statusC.test(i))
              mUi->rtcmRTKMsgInUseLed->setColor(Qt::green);
            else
              mUi->rtcmRTKMsgInUseLed->setColor(Qt::red);
            break;
          case 9:
            if (statusC.test(i))
              mUi->cmrRTKMsgInUseLed->setColor(Qt::green);
            else
              mUi->cmrRTKMsgInUseLed->setColor(Qt::red);
            break;
          case 10:
            if (statusC.test(i))
              mUi->iinDRModeLed->setColor(Qt::green);
            else
              mUi->iinDRModeLed->setColor(Qt::red);
            break;
          case 11:
            if (statusC.test(i))
              mUi->iinGPSLed->setColor(Qt::green);
            else
              mUi->iinGPSLed->setColor(Qt::red);
            break;
          case 12:
            if (statusC.test(i))
              mUi->iinCALed->setColor(Qt::green);
            else
              mUi->iinCALed->setColor(Qt::red);
            break;
          case 13:
            if (statusC.test(i))
              mUi->iinRTCMDGPSLed->setColor(Qt::green);
            else
              mUi->iinRTCMDGPSLed->setColor(Qt::red);
            break;
          case 14:
            if (statusC.test(i))
              mUi->iinDGPSLed->setColor(Qt::green);
            else
              mUi->iinDGPSLed->setColor(Qt::red);
            break;
          case 15:
            if (statusC.test(i))
              mUi->iinRTKLed->setColor(Qt::green);
            else
              mUi->iinRTKLed->setColor(Qt::red);
            break;
          case 16:
            if (statusC.test(i))
              mUi->iinWideRTKLed->setColor(Qt::green);
            else
              mUi->iinWideRTKLed->setColor(Qt::red);
            break;
          case 17:
            if (statusC.test(i))
              mUi->iinNarrowRTKLed->setColor(Qt::green);
            else
              mUi->iinNarrowRTKLed->setColor(Qt::red);
            break;
          case 18:
            if (statusC.test(i))
              mUi->recRTCM1Led->setColor(Qt::green);
            else
              mUi->recRTCM1Led->setColor(Qt::red);
            break;
          case 19:
            if (statusC.test(i))
              mUi->recRTCM3Led->setColor(Qt::green);
            else
              mUi->recRTCM3Led->setColor(Qt::red);
            break;
          case 20:
            if (statusC.test(i))
              mUi->recRTCM9Led->setColor(Qt::green);
            else
              mUi->recRTCM9Led->setColor(Qt::red);
            break;
          case 21:
            if (statusC.test(i))
              mUi->recRTCM18Led->setColor(Qt::green);
            else
              mUi->recRTCM18Led->setColor(Qt::red);
            break;
          case 22:
            if (statusC.test(i))
              mUi->recRTCM19Led->setColor(Qt::green);
            else
              mUi->recRTCM19Led->setColor(Qt::red);
            break;
          case 23:
            if (statusC.test(i))
              mUi->recCMR0Led->setColor(Qt::green);
            else
              mUi->recCMR0Led->setColor(Qt::red);
            break;
          case 24:
            if (statusC.test(i))
              mUi->recCMR1Led->setColor(Qt::green);
            else
              mUi->recCMR1Led->setColor(Qt::red);
            break;
          case 25:
            if (statusC.test(i))
              mUi->recCMR2Led->setColor(Qt::green);
            else
              mUi->recCMR2Led->setColor(Qt::red);
            break;
          case 26:
            if (statusC.test(i))
              mUi->recCMR94Led->setColor(Qt::green);
            else
              mUi->recCMR94Led->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
    }
  }
}
