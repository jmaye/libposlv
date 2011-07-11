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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file sendMsg.cpp
    \brief This file is a testing binary for sending a message to the Applanix.
  */

#include "com/POSLVControl.h"
#include "types/InstallationCalibrationControl.h"
#include "base/Factory.h"
#include "types/Acknowledge.h"

#include <cstdlib>

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
    return -1;
  }

  POSLVControl device(argv[1], atoi(argv[2]));
  device.open();

  Message* msg = Factory<uint16_t, Message>::getInstance().create(57);
  InstallationCalibrationControl& cal =
    msg->typeCast<InstallationCalibrationControl>();
  cal.mTransactionNumber = 10;
  cal.mCalibrationAction = 3;
  cal.mCalibrationSelect = 2;
  const Acknowledge& ackMsg = device.sendMessage(cal)->typeCast<Acknowledge>();
  std::cout << "Return status:" << ackMsg.mResponseCode << std::endl;
  delete &ackMsg;
  delete msg;

  device.close();

  return 0;
}
