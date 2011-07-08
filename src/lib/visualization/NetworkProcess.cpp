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

#include "visualization/NetworkProcess.h"

#include <iostream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NetworkProcess::NetworkProcess(double pollTime) :
  mPollTime(pollTime) {
  mpPollTimer = new QTimer(this);
  connect(mpPollTimer, SIGNAL(timeout()), this, SLOT(update()));
  mpPollTimer->start(mPollTime);
}

NetworkProcess::~NetworkProcess() {
  delete mpPollTimer;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double NetworkProcess::getPollTime() const {
  return mPollTime;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NetworkProcess::update() {
  try {
    const Group* group = mDevice.readGroup();
    if (group == NULL)
      return;
    emit groupRead(group);
    delete group;
  }
  catch (const IOException& e) {
    std::cout << e.what() << std::endl;
  }
}
