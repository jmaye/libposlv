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

#include "visualization/ReadThreadGroup.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ReadThreadGroup::ReadThreadGroup(double pollTime) :
  mPollTime(pollTime),
  mDevice("129.132.39.171", 5602) {
}

ReadThreadGroup::~ReadThreadGroup() {
  while (mGroupPtrList.size()) {
    delete mGroupPtrList.front();
    mGroupPtrList.pop_front();
  }
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double ReadThreadGroup::getPollTime() const {
  return mPollTime;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ReadThreadGroup::run() {
  while (true) {
    try {
      const Group* group = mDevice.readGroup();
      if (group == NULL)
        continue;
      emit groupRead(group);
      mGroupPtrList.push_back(group);
      if (mGroupPtrList.size() > 100) {
        delete mGroupPtrList.front();
        mGroupPtrList.pop_front();
      }
      emit deviceConnected(true);
    }
    catch (const IOException& e) {
      std::cout << e.what() << std::endl;
      emit deviceConnected(false);
    }
    //usleep(mPollTime * 1e6);
  }
}
