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

#include "visualization/ReadThreadGroup.h"
#include "types/GeneralStatusFDIR.h"
#include "ui_StatusControl.h"

#include <bitset>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

StatusControl::StatusControl() :
  mpUi(new Ui_StatusControl()) {
  mpUi->setupUi(this);

  connect(&ReadThreadGroup::getInstance(), SIGNAL(groupRead(const Group*)),
    this, SLOT(groupRead(const Group*)));

  mpUi->coarseLevelingActiveLed->setColor(Qt::red);
  mpUi->coarseLevelingFailedLed->setColor(Qt::red);
  mpUi->quadrantResolvedLed->setColor(Qt::red);
  mpUi->fineAlignActiveLed->setColor(Qt::red);
  mpUi->inertialNavInitLed->setColor(Qt::red);
  mpUi->inertialNavAlignActiveLed->setColor(Qt::red);
  mpUi->degNavSolLed->setColor(Qt::red);
  mpUi->refPrimGPSLed->setColor(Qt::red);
  mpUi->initPosValidLed->setColor(Qt::red);
  mpUi->fullNavSolLed->setColor(Qt::red);
  mpUi->logPortFileOpenLed->setColor(Qt::red);
  mpUi->logPortLogEnableLed->setColor(Qt::red);
  mpUi->LogPortDeviceFullLed->setColor(Qt::red);
  mpUi->ramConfigLed->setColor(Qt::red);
  mpUi->nvmWriteSuccessLed->setColor(Qt::red);
  mpUi->nvmReadFailLed->setColor(Qt::red);
  mpUi->nvmWriteFailLed->setColor(Qt::red);
  mpUi->cpuLoading55Led->setColor(Qt::red);
  mpUi->cpuLoading85Led->setColor(Qt::red);
  mpUi->logPortWriteErrorLed->setColor(Qt::red);
  mpUi->refSensor2Led->setColor(Qt::red);
  mpUi->refSensor1Led->setColor(Qt::red);

  mpUi->gamsInstallParamsLed->setColor(Qt::red);
  mpUi->primGPSRTKModeLed->setColor(Qt::red);
  mpUi->primGPSNotConfiguredLed->setColor(Qt::red);
  mpUi->gamsCalibReqLed->setColor(Qt::red);
  mpUi->attitudeRMSLed->setColor(Qt::red);
  mpUi->primGPSCAModeLed->setColor(Qt::red);
  mpUi->gamsCalibFailedLed->setColor(Qt::red);
  mpUi->primGPSResetLed->setColor(Qt::red);
  mpUi->velRMSLed->setColor(Qt::red);
  mpUi->gamsSolOkLed->setColor(Qt::red);
  mpUi->primGPSInitFailedLed->setColor(Qt::red);
  mpUi->gamsCalibProgressLed->setColor(Qt::red);
  mpUi->gamsCalibForcedLed->setColor(Qt::red);
  mpUi->primGPSConfigSentLed->setColor(Qt::red);
  mpUi->primGPSWideRTKModeLed->setColor(Qt::red);
  mpUi->headingRMSLed->setColor(Qt::red);
  mpUi->primGPSNavSolInUseLed->setColor(Qt::red);
  mpUi->gamsCalibSuspLed->setColor(Qt::red);
  mpUi->gamsSolInUseLed->setColor(Qt::red);
  mpUi->primGPSDIffModLed->setColor(Qt::red);
  mpUi->posRMSLed->setColor(Qt::red);
  mpUi->gamsCalibCompleteLed->setColor(Qt::red);
  mpUi->primGPSNarrowRTKModeLed->setColor(Qt::red);
  mpUi->secGPSObsLed->setColor(Qt::red);
  mpUi->primGPSObsLed->setColor(Qt::red);
  mpUi->primGPSPCodeLed->setColor(Qt::red);

  mpUi->cmrRTKMsgInUseLed->setColor(Qt::red);
  mpUi->iinDGPSLed->setColor(Qt::red);
  mpUi->iinDRModeLed->setColor(Qt::red);
  mpUi->iinRTCMDGPSLed->setColor(Qt::red);
  mpUi->recRTCM18Led->setColor(Qt::red);
  mpUi->zupdProcEnabledLed->setColor(Qt::red);
  mpUi->iinNarrowRTKLed->setColor(Qt::red);
  mpUi->iinWideRTKLed->setColor(Qt::red);
  mpUi->iinCALed->setColor(Qt::red);
  mpUi->rtcmRTKMsgInUseLed->setColor(Qt::red);
  mpUi->recCMR94Led->setColor(Qt::red);;
  mpUi->rtcmDiffCorrLed->setColor(Qt::red);
  mpUi->dmiInUseLed->setColor(Qt::red);
  mpUi->iinRTKLed->setColor(Qt::red);
  mpUi->recCMR0Led->setColor(Qt::red);
  mpUi->recRTCM19Led->setColor(Qt::red);
  mpUi->posFixInUseLed->setColor(Qt::red);
  mpUi->zupdInUseLed->setColor(Qt::red);
  mpUi->recCMR1Led->setColor(Qt::red);
  mpUi->recRTCM1Led->setColor(Qt::red);
  mpUi->iinGPSLed->setColor(Qt::red);
  mpUi->recCMR2Led->setColor(Qt::red);
  mpUi->recRTCM9Led->setColor(Qt::red);
  mpUi->recRTCM3Led->setColor(Qt::red);
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
    std::bitset<32> statusA(msg.mGeneralStatusA);
    std::bitset<32> statusB(msg.mGeneralStatusB);
    std::bitset<32> statusC(msg.mGeneralStatusC);
    for (size_t i = 0; i < 32; i++) {
      switch (i) {
        case 0:
          if (statusA.test(i))
            mpUi->coarseLevelingActiveLed->setColor(Qt::green);
          else
            mpUi->coarseLevelingActiveLed->setColor(Qt::red);
          break;
        case 1:
          if (statusA.test(i))
            mpUi->coarseLevelingFailedLed->setColor(Qt::green);
          else
            mpUi->coarseLevelingFailedLed->setColor(Qt::red);
          break;
        case 2:
          if (statusA.test(i))
            mpUi->quadrantResolvedLed->setColor(Qt::green);
          else
            mpUi->quadrantResolvedLed->setColor(Qt::red);
          break;
        case 3:
          if (statusA.test(i))
            mpUi->fineAlignActiveLed->setColor(Qt::green);
          else
            mpUi->fineAlignActiveLed->setColor(Qt::red);
          break;
        case 4:
          if (statusA.test(i))
            mpUi->inertialNavInitLed->setColor(Qt::green);
          else
            mpUi->inertialNavInitLed->setColor(Qt::red);
          break;
        case 5:
          if (statusA.test(i))
            mpUi->inertialNavAlignActiveLed->setColor(Qt::green);
          else
            mpUi->inertialNavAlignActiveLed->setColor(Qt::red);
          break;
        case 6:
          if (statusA.test(i))
            mpUi->degNavSolLed->setColor(Qt::green);
          else
            mpUi->degNavSolLed->setColor(Qt::red);
          break;
        case 7:
          if (statusA.test(i))
            mpUi->fullNavSolLed->setColor(Qt::green);
          else
            mpUi->fullNavSolLed->setColor(Qt::red);
          break;
        case 8:
          if (statusA.test(i))
            mpUi->initPosValidLed->setColor(Qt::green);
          else
            mpUi->initPosValidLed->setColor(Qt::red);
          break;
        case 9:
          if (statusA.test(i))
            mpUi->refPrimGPSLed->setColor(Qt::green);
          else
            mpUi->refPrimGPSLed->setColor(Qt::red);
          break;
        case 10:
          if (statusA.test(i))
            mpUi->refSensor1Led->setColor(Qt::green);
          else
            mpUi->refSensor1Led->setColor(Qt::red);
          break;
        case 11:
          if (statusA.test(i))
            mpUi->refSensor2Led->setColor(Qt::green);
          else
            mpUi->refSensor2Led->setColor(Qt::red);
          break;
        case 12:
          if (statusA.test(i))
            mpUi->logPortWriteErrorLed->setColor(Qt::green);
          else
            mpUi->logPortWriteErrorLed->setColor(Qt::red);
          break;
        case 13:
          if (statusA.test(i))
            mpUi->logPortFileOpenLed->setColor(Qt::green);
          else
            mpUi->logPortFileOpenLed->setColor(Qt::red);
          break;
        case 14:
          if (statusA.test(i))
            mpUi->logPortLogEnableLed->setColor(Qt::green);
          else
            mpUi->logPortLogEnableLed->setColor(Qt::red);
          break;
        case 15:
          if (statusA.test(i))
            mpUi->LogPortDeviceFullLed->setColor(Qt::green);
          else
            mpUi->LogPortDeviceFullLed->setColor(Qt::red);
          break;
        case 16:
          if (statusA.test(i))
            mpUi->ramConfigLed->setColor(Qt::green);
          else
            mpUi->ramConfigLed->setColor(Qt::red);
          break;
        case 17:
          if (statusA.test(i))
            mpUi->nvmWriteSuccessLed->setColor(Qt::green);
          else
            mpUi->nvmWriteSuccessLed->setColor(Qt::red);
          break;
        case 18:
          if (statusA.test(i))
            mpUi->nvmWriteFailLed->setColor(Qt::green);
          else
            mpUi->nvmWriteFailLed->setColor(Qt::red);
          break;
        case 19:
          if (statusA.test(i))
            mpUi->nvmReadFailLed->setColor(Qt::green);
          else
            mpUi->nvmReadFailLed->setColor(Qt::red);
          break;
        case 20:
          if (statusA.test(i))
            mpUi->cpuLoading55Led->setColor(Qt::green);
          else
            mpUi->cpuLoading55Led->setColor(Qt::red);
          break;
        case 21:
          if (statusA.test(i))
            mpUi->cpuLoading85Led->setColor(Qt::green);
          else
            mpUi->cpuLoading85Led->setColor(Qt::red);
          break;
        default:
          break;
      }
    }

    for (size_t i = 0; i < 32; i++) {
      switch (i) {
        case 0:
          if (statusB.test(i))
            mpUi->attitudeRMSLed->setColor(Qt::green);
          else
            mpUi->attitudeRMSLed->setColor(Qt::red);
          break;
        case 1:
          if (statusB.test(i))
            mpUi->headingRMSLed->setColor(Qt::green);
          else
            mpUi->headingRMSLed->setColor(Qt::red);
          break;
        case 2:
          if (statusB.test(i))
            mpUi->posRMSLed->setColor(Qt::green);
          else
            mpUi->posRMSLed->setColor(Qt::red);
          break;
        case 3:
          if (statusB.test(i))
            mpUi->velRMSLed->setColor(Qt::green);
          else
            mpUi->velRMSLed->setColor(Qt::red);
          break;
        case 4:
          if (statusB.test(i))
            mpUi->gamsCalibProgressLed->setColor(Qt::green);
          else
            mpUi->gamsCalibProgressLed->setColor(Qt::red);
          break;
        case 5:
          if (statusB.test(i))
            mpUi->gamsCalibCompleteLed->setColor(Qt::green);
          else
            mpUi->gamsCalibCompleteLed->setColor(Qt::red);
          break;
        case 6:
          if (statusB.test(i))
            mpUi->gamsCalibFailedLed->setColor(Qt::green);
          else
            mpUi->gamsCalibFailedLed->setColor(Qt::red);
          break;
        case 7:
          if (statusB.test(i))
            mpUi->gamsCalibReqLed->setColor(Qt::green);
          else
            mpUi->gamsCalibReqLed->setColor(Qt::red);
          break;
        case 8:
          if (statusB.test(i))
            mpUi->gamsInstallParamsLed->setColor(Qt::green);
          else
            mpUi->gamsInstallParamsLed->setColor(Qt::red);
          break;
        case 9:
          if (statusB.test(i))
            mpUi->gamsSolInUseLed->setColor(Qt::green);
          else
            mpUi->gamsSolInUseLed->setColor(Qt::red);
          break;
        case 10:
          if (statusB.test(i))
            mpUi->gamsSolOkLed->setColor(Qt::green);
          else
            mpUi->gamsSolOkLed->setColor(Qt::red);
          break;
        case 11:
          if (statusB.test(i))
            mpUi->gamsCalibSuspLed->setColor(Qt::green);
          else
            mpUi->gamsCalibSuspLed->setColor(Qt::red);
          break;
        case 12:
          if (statusB.test(i))
            mpUi->gamsCalibForcedLed->setColor(Qt::green);
          else
            mpUi->gamsCalibForcedLed->setColor(Qt::red);
          break;
        case 13:
          if (statusB.test(i))
            mpUi->primGPSNavSolInUseLed->setColor(Qt::green);
          else
            mpUi->primGPSNavSolInUseLed->setColor(Qt::red);
          break;
        case 14:
          if (statusB.test(i))
            mpUi->primGPSInitFailedLed->setColor(Qt::green);
          else
            mpUi->primGPSInitFailedLed->setColor(Qt::red);
          break;
        case 15:
          if (statusB.test(i))
            mpUi->primGPSResetLed->setColor(Qt::green);
          else
            mpUi->primGPSResetLed->setColor(Qt::red);
          break;
        case 16:
          if (statusB.test(i))
            mpUi->primGPSConfigSentLed->setColor(Qt::green);
          else
            mpUi->primGPSConfigSentLed->setColor(Qt::red);
          break;
        case 17:
          if (statusB.test(i))
            mpUi->primGPSNotConfiguredLed->setColor(Qt::green);
          else
            mpUi->primGPSNotConfiguredLed->setColor(Qt::red);
          break;
        case 18:
          if (statusB.test(i))
            mpUi->primGPSCAModeLed->setColor(Qt::green);
          else
            mpUi->primGPSCAModeLed->setColor(Qt::red);
          break;
        case 19:
          if (statusB.test(i))
            mpUi->primGPSDIffModLed->setColor(Qt::green);
          else
            mpUi->primGPSDIffModLed->setColor(Qt::red);
          break;
        case 20:
          if (statusB.test(i))
            mpUi->primGPSRTKModeLed->setColor(Qt::green);
          else
            mpUi->primGPSRTKModeLed->setColor(Qt::red);
          break;
        case 21:
          if (statusB.test(i))
            mpUi->primGPSWideRTKModeLed->setColor(Qt::green);
          else
            mpUi->primGPSWideRTKModeLed->setColor(Qt::red);
          break;
        case 22:
          if (statusB.test(i))
            mpUi->primGPSNarrowRTKModeLed->setColor(Qt::green);
          else
            mpUi->primGPSNarrowRTKModeLed->setColor(Qt::red);
          break;
        case 23:
          if (statusB.test(i))
            mpUi->primGPSObsLed->setColor(Qt::green);
          else
            mpUi->primGPSObsLed->setColor(Qt::red);
          break;
        case 24:
          if (statusB.test(i))
            mpUi->secGPSObsLed->setColor(Qt::green);
          else
            mpUi->secGPSObsLed->setColor(Qt::red);
          break;
        case 31:
          if (statusB.test(i))
            mpUi->primGPSPCodeLed->setColor(Qt::green);
          else
            mpUi->primGPSPCodeLed->setColor(Qt::red);
          break;
      }
    }

    for (size_t i = 0; i < 32; i++) {
      switch (i) {
        case 2:
          if (statusC.test(i))
            mpUi->dmiInUseLed->setColor(Qt::green);
          else
            mpUi->dmiInUseLed->setColor(Qt::red);
          break;
        case 3:
          if (statusC.test(i))
            mpUi->zupdProcEnabledLed->setColor(Qt::green);
          else
            mpUi->zupdProcEnabledLed->setColor(Qt::red);
          break;
        case 4:
          if (statusC.test(i))
            mpUi->zupdInUseLed->setColor(Qt::green);
          else
            mpUi->zupdInUseLed->setColor(Qt::red);
          break;
        case 5:
          if (statusC.test(i))
            mpUi->posFixInUseLed->setColor(Qt::green);
          else
            mpUi->posFixInUseLed->setColor(Qt::red);
          break;
        case 6:
          if (statusC.test(i))
            mpUi->rtcmDiffCorrLed->setColor(Qt::green);
          else
            mpUi->rtcmDiffCorrLed->setColor(Qt::red);
          break;
        case 7:
          if (statusC.test(i))
            mpUi->rtcmRTKMsgInUseLed->setColor(Qt::green);
          else
            mpUi->rtcmRTKMsgInUseLed->setColor(Qt::red);
          break;
        case 9:
          if (statusC.test(i))
            mpUi->cmrRTKMsgInUseLed->setColor(Qt::green);
          else
            mpUi->cmrRTKMsgInUseLed->setColor(Qt::red);
          break;
        case 10:
          if (statusC.test(i))
            mpUi->iinDRModeLed->setColor(Qt::green);
          else
            mpUi->iinDRModeLed->setColor(Qt::red);
          break;
        case 11:
          if (statusC.test(i))
            mpUi->iinGPSLed->setColor(Qt::green);
          else
            mpUi->iinGPSLed->setColor(Qt::red);
          break;
        case 12:
          if (statusC.test(i))
            mpUi->iinCALed->setColor(Qt::green);
          else
            mpUi->iinCALed->setColor(Qt::red);
          break;
        case 13:
          if (statusC.test(i))
            mpUi->iinRTCMDGPSLed->setColor(Qt::green);
          else
            mpUi->iinRTCMDGPSLed->setColor(Qt::red);
          break;
        case 14:
          if (statusC.test(i))
            mpUi->iinDGPSLed->setColor(Qt::green);
          else
            mpUi->iinDGPSLed->setColor(Qt::red);
          break;
        case 15:
          if (statusC.test(i))
            mpUi->iinRTKLed->setColor(Qt::green);
          else
            mpUi->iinRTKLed->setColor(Qt::red);
          break;
        case 16:
          if (statusC.test(i))
            mpUi->iinWideRTKLed->setColor(Qt::green);
          else
            mpUi->iinWideRTKLed->setColor(Qt::red);
          break;
        case 17:
          if (statusC.test(i))
            mpUi->iinNarrowRTKLed->setColor(Qt::green);
          else
            mpUi->iinNarrowRTKLed->setColor(Qt::red);
          break;
        case 18:
          if (statusC.test(i))
            mpUi->recRTCM1Led->setColor(Qt::green);
          else
            mpUi->recRTCM1Led->setColor(Qt::red);
          break;
        case 19:
          if (statusC.test(i))
            mpUi->recRTCM3Led->setColor(Qt::green);
          else
            mpUi->recRTCM3Led->setColor(Qt::red);
          break;
        case 20:
          if (statusC.test(i))
            mpUi->recRTCM9Led->setColor(Qt::green);
          else
            mpUi->recRTCM9Led->setColor(Qt::red);
          break;
        case 21:
          if (statusC.test(i))
            mpUi->recRTCM18Led->setColor(Qt::green);
          else
            mpUi->recRTCM18Led->setColor(Qt::red);
          break;
        case 22:
          if (statusC.test(i))
            mpUi->recRTCM19Led->setColor(Qt::green);
          else
            mpUi->recRTCM19Led->setColor(Qt::red);
          break;
        case 23:
          if (statusC.test(i))
            mpUi->recCMR0Led->setColor(Qt::green);
          else
            mpUi->recCMR0Led->setColor(Qt::red);
          break;
        case 24:
          if (statusC.test(i))
            mpUi->recCMR1Led->setColor(Qt::green);
          else
            mpUi->recCMR1Led->setColor(Qt::red);
          break;
        case 25:
          if (statusC.test(i))
            mpUi->recCMR2Led->setColor(Qt::green);
          else
            mpUi->recCMR2Led->setColor(Qt::red);
          break;
        case 26:
          if (statusC.test(i))
            mpUi->recCMR94Led->setColor(Qt::green);
          else
            mpUi->recCMR94Led->setColor(Qt::red);
          break;
        default:
          break;
      }
    }
  }
}
