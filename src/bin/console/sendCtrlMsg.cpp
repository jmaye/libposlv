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

/** \file sendCtrlMsg.cpp
    \brief This file is a testing binary for sending a message to the Applanix.
  */

#include <cstdlib>

#include "com/TCPConnectionClient.h"
#include "sensor/POSLVComTCP.h"
#include "base/Factory.h"
#include "types/Message.h"
#include "types/InstallationCalibrationControl.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <IP> <Port>" << std::endl;
    return -1;
  }
  TCPConnectionClient connection(argv[1], atoi(argv[2]));
  POSLVComTCP device(connection);
  boost::shared_ptr<Message> msg(
    Factory<uint16_t, Message>::getInstance().create(57));
  InstallationCalibrationControl& calMsg =
    msg->typeCast<InstallationCalibrationControl>();
  calMsg.mTransactionNumber = 10;
  calMsg.mCalibrationAction = 3;
  calMsg.mCalibrationSelect = 0xFF;
  device.sendMessage(calMsg);
  return 0;
}
