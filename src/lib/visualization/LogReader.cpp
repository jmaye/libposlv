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

#include "visualization/LogReader.h"

#include "sensor/BinaryLogReader.h"
#include "types/Packet.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LogReader::LogReader(BinaryLogReader& device, double pollingTime) :
    mDevice(device),
    mPollingTime(pollingTime) {
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
  mTimer.setInterval(pollingTime);
  mTimer.start();
}

LogReader::~LogReader() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double LogReader::getPollingTime() const {
  return mPollingTime;
}

void LogReader::setPollingTime(double pollingTime) {
  mPollingTime = pollingTime;
  mTimer.setInterval(pollingTime);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void LogReader::timerTimeout() {
  if (mDevice.getStream().good()) {
    double timestamp;
    mDevice >> timestamp;
    emit readPacket(mDevice.readPacket());
    emit deviceConnected(true);
  }
  else
    emit comException("LogReader::timerTimeout(): stream not ready");
}
