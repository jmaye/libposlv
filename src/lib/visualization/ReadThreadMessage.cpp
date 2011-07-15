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

#include "visualization/ReadThreadMessage.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ReadThreadMessage::ReadThreadMessage(double pollTime) :
  mPollTime(pollTime),
  mDevice(5600) {
}

ReadThreadMessage::~ReadThreadMessage() {
  while (mMessagePtrList.size()) {
    delete mMessagePtrList.front();
    mMessagePtrList.pop_front();
  }
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double ReadThreadMessage::getPollTime() const {
  return mPollTime;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ReadThreadMessage::run() {
  while (true) {
    try {
      const Message* message = mDevice.readMessage();
      if (message == NULL)
        continue;
      emit messageRead(message);
      mMessagePtrList.push_back(message);
      if (mMessagePtrList.size() > 100) {
        delete mMessagePtrList.front();
        mMessagePtrList.pop_front();
      }
    }
    catch (const IOException& e) {
      std::cout << e.what() << std::endl;
    }
    usleep(mPollTime * 1e6);
  }
}
