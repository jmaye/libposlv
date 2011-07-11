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

#include <sstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

StatusControl::StatusControl() :
  mpUi(new Ui_StatusControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusAMsg[0] = "Coarse leveling active";
  mStatusAMsg[1] = "Coarse leveling failed";
  mStatusAMsg[2] = "Quadrant resolved";
  mStatusAMsg[3] = "Fine align active";
  mStatusAMsg[4] = "Inertial navigator initialized";
  mStatusAMsg[5] = "Inertial navigator alignment active";
  mStatusAMsg[6] = "Degraded navigation solution";
  mStatusAMsg[7] = "Full navigation solution";
  mStatusAMsg[8] = "Initial position valid";
  mStatusAMsg[9] = "Reference to Primary GPS Lever arms = 0";
  mStatusAMsg[10] = "Reference to Sensor 1 Lever arms = 0";
  mStatusAMsg[11] = "Reference to Sensor 2 Lever arms = 0";
  mStatusAMsg[12] = "Logging Port file write error";
  mStatusAMsg[13] = "Logging Port file open";
  mStatusAMsg[14] = "Logging Port logging enabled";
  mStatusAMsg[15] = "Logging Port device full";
  mStatusAMsg[16] = "RAM configuration differs from NVM";
  mStatusAMsg[17] = "NVM write successful";
  mStatusAMsg[18] = "NVM write fail";
  mStatusAMsg[19] = "NVM read fail";
  mStatusAMsg[20] = "CPU loading exceeds 55% threshold";
  mStatusAMsg[21] = "CPU loading exceeds 85% threshold";

  mStatusBMsg[0] = "User attitude RMS performance";
  mStatusBMsg[1] = "User heading RMS performance";
  mStatusBMsg[2] = "User position RMS performance";
  mStatusBMsg[3] = "User velocity RMS performance";
  mStatusBMsg[4] = "GAMS calibration in progress";
  mStatusBMsg[5] = "GAMS calibration complete";
  mStatusBMsg[6] = "GAMS calibration failed";
  mStatusBMsg[7] = "GAMS calibration requested";
  mStatusBMsg[8] = "GAMS installation parameters valid";
  mStatusBMsg[9] = "GAMS solution in use";
  mStatusBMsg[10] = "GAMS solution OK";
  mStatusBMsg[11] = "GAMS calibration suspended";
  mStatusBMsg[12] = "GAMS calibration forced";
  mStatusBMsg[13] = "Primary GPS navigation solution in use";
  mStatusBMsg[14] = "Primary GPS initialization failed";
  mStatusBMsg[15] = "Primary GPS reset command sent";
  mStatusBMsg[16] = "Primary GPS configuration file sent";
  mStatusBMsg[17] = "Primary GPS not configured";
  mStatusBMsg[18] = "Primary GPS in C/A mode";
  mStatusBMsg[19] = "Primary GPS in Differential mode";
  mStatusBMsg[20] = "Primary GPS in float RTK mode";
  mStatusBMsg[21] = "Primary GPS in wide lane RTK mode";
  mStatusBMsg[22] = "Primary GPS in narrow lane RTK mode";
  mStatusBMsg[23] = "Primary GPS observables in use";
  mStatusBMsg[24] = "Secondary GPS observables in use";
  mStatusBMsg[25] = "Auxiliary GPS navigation solution in use";
  mStatusBMsg[26] = "Auxiliary GPS in P-code mode";
  mStatusBMsg[27] = "Auxiliary GPS in Differential mode";
  mStatusBMsg[28] = "Auxiliary GPS in float RTK mode";
  mStatusBMsg[29] = "Auxiliary GPS in wide lane RTK mode";
  mStatusBMsg[30] = "Auxiliary GPS in narrow lane RTK mode";
  mStatusBMsg[31] = "Primary GPS in P-code mode";

  mStatusCMsg[2] = "DMI data in use";
  mStatusCMsg[3] = "ZUPD processing enabled";
  mStatusCMsg[4] = "ZUPD in use";
  mStatusCMsg[5] = "Position fix in use";
  mStatusCMsg[6] = "RTCM differential corrections";
  mStatusCMsg[7] = "RTCM RTK messages in use";
  mStatusCMsg[9] = "CMR RTK messages in use";
  mStatusCMsg[10] = "IIN in DR mode";
  mStatusCMsg[11] = "IIN GPS aiding is loosely coupled";
  mStatusCMsg[12] = "IIN in C/A GPS aided mode";
  mStatusCMsg[13] = "IIN in RTCM DGPS aided mode";
  mStatusCMsg[14] = "IIN in code DGPS aided mode";
  mStatusCMsg[15] = "IIN in float RTK aided mode";
  mStatusCMsg[16] = "IIN in wide lane RTK aided mode";
  mStatusCMsg[17] = "IIN in narrow lane RTK aided mode";
  mStatusCMsg[18] = "Received RTCM Type 1 message";
  mStatusCMsg[19] = "Received RTCM Type 3 message";
  mStatusCMsg[20] = "Received RTCM Type 9 message";
  mStatusCMsg[21] = "Received RTCM Type 18 messages";
  mStatusCMsg[22] = "Received RTCM Type 19 messages";
  mStatusCMsg[23] = "Received CMR Type 0 message";
  mStatusCMsg[24] = "Received CMR Type 1 message";
  mStatusCMsg[25] = "Received CMR Type 2 message";
  mStatusCMsg[26] = "Received CMR Type 94 message";

  mFDIR1Msg[0] = "IMU-POS checksum error";
  mFDIR1Msg[1] = "IMU status set by IMU";
  mFDIR1Msg[2] = "Successive IMU failures";
  mFDIR1Msg[3] = "IIN configuration mismatch failure";
  mFDIR1Msg[5] = "Primary GPS not in Navigation mode";
  mFDIR1Msg[6] = "Primary GPS not available for alignment";
  mFDIR1Msg[7] = "Primary data gap";
  mFDIR1Msg[8] = "Primary GPS PPS time gap";
  mFDIR1Msg[9] = "Primary GPS time recovery data not received";
  mFDIR1Msg[10] = "Primary GPS observable data gap";
  mFDIR1Msg[11] = "Primary ephemeris data gap";
  mFDIR1Msg[12] = "Primary GPS excessive lock-time resets";
  mFDIR1Msg[13] = "Primary GPS missing ephemeris";
  mFDIR1Msg[16] = "Primary GPS SNR failure";
  mFDIR1Msg[17] = "Base GPS data gap";
  mFDIR1Msg[18] = "Base GPS parity error";
  mFDIR1Msg[19] = "Base GPS message rejected";
  mFDIR1Msg[20] = "Secondary GPS data gap";
  mFDIR1Msg[21] = "Secondary GPS observable data gap";
  mFDIR1Msg[22] = "Secondary GPS SNR failure";
  mFDIR1Msg[23] = "Secondary GPS excessive lock-time resets";
  mFDIR1Msg[25] = "Auxiliary GPS data gap";
  mFDIR1Msg[26] = "GAMS ambiguity resolution failed";
  mFDIR1Msg[28] = "DMI failed or is offline";
  mFDIR1Msg[30] = "IIN WL ambiguity error";
  mFDIR1Msg[31] = "IIN NL ambiguity error";

  mFDIR2Msg[0] = "Inertial speed exceeds maximum";
  mFDIR2Msg[1] = "Primary GPS velocity exceeds maximum";
  mFDIR2Msg[2] = "Primary GPS position error exceeds maximum";
  mFDIR2Msg[3] = "Auxiliary GPS position error exceeds maximum";
  mFDIR2Msg[4] = "DMI speed exceeds maximum";

  mFDIR4Msg[0] = "Primary GPS position rejected";
  mFDIR4Msg[1] = "Primary GPS velocity rejected";
  mFDIR4Msg[2] = "GAMS heading rejected";
  mFDIR4Msg[3] = "Auxiliary GPS data rejected";
  mFDIR4Msg[4] = "DMI data rejected";
  mFDIR4Msg[5] = "Primary GPS observables rejected";

  mFDIR5Msg[0] = "X accelerometer failure";
  mFDIR5Msg[1] = "Y accelerometer failure";
  mFDIR5Msg[2] = "Z accelerometer failure";
  mFDIR5Msg[3] = "X gyro failure";
  mFDIR5Msg[4] = "Y gyro failure";
  mFDIR5Msg[5] = "Z gyro failure";
  mFDIR5Msg[6] = "Excessive GAMS heading offset";
  mFDIR5Msg[7] = "Excessive primary GPS lever arm error";
  mFDIR5Msg[8] = "Excessive auxiliary 1 GPS lever arm error";
  mFDIR5Msg[9] = "Excessive auxiliary 2 GPS lever arm error";
  mFDIR5Msg[10] = "Excessive POS position error RMS";
  mFDIR5Msg[11] = "Excessive primary GPS clock drift";

  mExtStatusMsg[0] = "Primary GPS in Omnistar HP mode";
  mExtStatusMsg[1] = "Primary GPS in Omnistar XP mode";
  mExtStatusMsg[2] = "Primary GPS in Omnistar VBS mode";
  mExtStatusMsg[3] = "Primary GPS in PPP mode";
  mExtStatusMsg[4] = "Aux. GPS in Omnistar HP mode";
  mExtStatusMsg[5] = "Aux. GPS in Omnistar XP mode";
  mExtStatusMsg[6] = "Aux. GPS in Omnistar VBS mode";
  mExtStatusMsg[7] = "Aux. GPS in PPP mode";

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
    std::stringstream statusA;
    for (size_t i = 0; i <= 21; i++)
      if ((msg.mGeneralStatusA >> i) & 0x00000001)
        statusA << mStatusAMsg[i] << std::endl;
    mpUi->statusAText->setText(statusA.str().c_str());
    std::stringstream statusB;
    for (size_t i = 0; i <= 31; i++)
      if ((msg.mGeneralStatusB >> i) & 0x00000001)
        statusB << mStatusBMsg[i] << std::endl;
    mpUi->statusBText->setText(statusB.str().c_str());
    std::stringstream statusC;
    for (size_t i = 2; i <= 26; i++)
      if ((msg.mGeneralStatusC >> i) & 0x00000001 && i != 8)
        statusC << mStatusCMsg[i] << std::endl;
    mpUi->statusCText->setText(statusC.str().c_str());
    mpUi->fdir1IMUSpinBox->setValue(msg.mFDIRLevel1Failures);
    std::stringstream fdir1;
    for (size_t i = 0; i <= 31; i++)
      if ((msg.mFDIRLevel1Status >> i) & 0x00000001 && i != 4 && i != 14 &&
        i != 15 && i != 24 && i != 28 && i != 29)
        fdir1 << mFDIR1Msg[i] << std::endl;
    mpUi->fdir1Text->setText(fdir1.str().c_str());
    std::stringstream fdir2;
    for (size_t i = 0; i <= 4; i++)
      if ((msg.mFDIRLevel2Status >> i) & 0x0001)
        fdir2 << mFDIR2Msg[i] << std::endl;
    mpUi->fdir2Text->setText(fdir2.str().c_str());
    std::stringstream fdir4;
    for (size_t i = 0; i <= 5; i++)
      if ((msg.mFDIRLevel4Status >> i) & 0x0001)
        fdir4 << mFDIR4Msg[i] << std::endl;
    mpUi->fdir4Text->setText(fdir4.str().c_str());
    std::stringstream fdir5;
    for (size_t i = 0; i <= 11; i++)
      if ((msg.mFDIRLevel5Status >> i) & 0x0001)
        fdir5 << mFDIR5Msg[i] << std::endl;
    mpUi->fdir5Text->setText(fdir5.str().c_str());
    std::stringstream extStatus;
    for (size_t i = 0; i <= 7; i++)
      if ((msg.mExtendedStatus >> i) & 0x00000001)
        extStatus << mExtStatusMsg[i] << std::endl;
    mpUi->extStatusText->setText(extStatus.str().c_str());
  }
}
