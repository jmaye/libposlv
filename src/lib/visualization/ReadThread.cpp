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

#include "visualization/ReadThread.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ReadThread::ReadThread(double pollTime) :
  mPollTime(pollTime) {
  mpTimer = new QTimer(this);
  connect(mpTimer, SIGNAL(timeout()), this, SLOT(update()));
  mpTimer->start(1);
}

ReadThread::~ReadThread() {
  delete mpTimer;
  while (mGroupPtrList.size()) {
    delete mGroupPtrList.front();
    mGroupPtrList.pop_front();
  }
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double ReadThread::getPollTime() const {
  return mPollTime;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ReadThread::run() {
  while (true) {
    try {
      const Group* group = mDevice.readGroup();
      if (group == NULL)
        continue;
      emit groupRead(group);
      emit deviceConnected(true);
      mGroupPtrList.push_back(group);
    }
    catch (const IOException& e) {
      std::cout << e.what() << std::endl;
      emit deviceConnected(false);
    }
    //usleep(mPollTime * 1e6);
  }
}

void ReadThread::update() {
  while (mGroupPtrList.size() > 100) {
    delete mGroupPtrList.front();
    mGroupPtrList.pop_front();
  }
}
