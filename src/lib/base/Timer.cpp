/***************************************************************************
 *   Copyright (C) 2004 by Ralf Kaestner                                   *
 *   ralf.kaestner@gmail.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <sys/time.h>
#include <limits>

#include "timer.hpp"

#include "inputstream.hpp"
#include "outputstream.hpp"
#include "threads.hpp"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Timer::Timer(bool start) :
  startTime(0.0),
  period(0.0) {
  if (start) this->start();
}

Timer::Timer(const Timer& src) :
  startTime(src.startTime),
  period(src.period) {
}

Timer::~Timer() {
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

double Timer::getPeriod() const {
  return period;
}

double Timer::getFrequency() const {
  return 1.0/period;
}

const Timestamp& Timer::getStartTime() const {
  return startTime;
}

double Timer::getLeft(double period) const {
  return startTime+period-Timestamp::now();
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

Timer& Timer::assign(const Timer& src) {
  startTime = src.startTime;
  period = src.period;

  return *this;
}

Timer& Timer::operator=(const Timer& src) {
  return assign(src);
}

void Timer::start(bool reset) {
  if (reset) this->reset();
  startTime = Timestamp::now();
}

void Timer::stop(double period) {
  sleep(getLeft(period));
  this->period += Timestamp::now()-startTime;
}

void Timer::reset() {
  startTime = 0.0;
  period = 0.0;
}

void Timer::wait(double period) const {
  sleep(getLeft(period));
}

void Timer::sleep(double period) {
  if (period > 0.0) {
    timespec time = Timestamp(period);

    Thread* self = 0;
    try {
      self = &Threads::getInstance().getSelf();
    }
    catch (Exception& exception) {
      self = 0;
    }

    Thread::State threadState;
    if (self) threadState = self->setState(Thread::sleeping);

    nanosleep(&time, 0);

    if (self) self->setState(threadState);
  }
}

double Timer::eternal() {
  return std::numeric_limits<double>::max();
}

void Timer::read(InputStream& stream) {
  stream.begin(StreamContext::allocate);
  stream >> startTime >> period;
  stream.end(StreamContext::allocate);
}

void Timer::write(OutputStream& stream) const {
  stream.begin(StreamContext::allocate);
  stream << startTime << period;
  stream.end(StreamContext::allocate);
}

bool Timer::hasBase(const TypeInfo& type) const {
  return Type<Timer>::hasBase<Class>(type);
}
