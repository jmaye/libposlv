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

#include "condition.hpp"

#include "mutex.hpp"
#include "threads.hpp"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <> EnumeratableType<Condition::SignalType>::Range::Range() {
  (*this)[Condition::unicast] = "unicast";
  (*this)[Condition::broadcast] = "broadcast";
}

Condition::Condition() {
  pthread_cond_init(&identifier, 0);
}

Condition::~Condition() {
  pthread_cond_destroy(&identifier);
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

void Condition::signal(SignalType signalType) {
  if (signalType == broadcast)
    pthread_cond_broadcast(&identifier);
  else
    pthread_cond_signal(&identifier);
}

bool Condition::wait(Mutex& mutex, double seconds) const {
  bool result = true;

  if (seconds > 0.0) {
    pthread_mutex_lock(&mutex.identifier);
    mutex.safeUnlock();
  
    bool result = safeWait(mutex, seconds);
  
    mutex.safeLock(Timer::eternal());
    pthread_mutex_unlock(&mutex.identifier);
  }

  return result;
}

bool Condition::hasBase(const TypeInfo& type) const {
  return Type<Condition>::hasBase<Class>(type);
}

bool Condition::safeWait(const Mutex& mutex, double seconds) const {
  bool result = true;

  Thread* self = 0;
  try {
    self = &Threads::getInstance().getSelf();
  }
  catch (Exception& exception) {
    self = 0;
  }

  Thread::State threadState;
  if (self) {
    if (&mutex == &self->mutex)
      threadState = self->safeSetState(Thread::waiting);
    else 
      threadState = self->setState(Thread::waiting);
  }

  if (seconds == Timer::eternal())
    result = safeEternalWait(mutex);
  else if (seconds > 0.0)
    result = safeWaitUntil(mutex, Timestamp(Timestamp::now()+seconds));

  if (self) {
    if (&mutex == &self->mutex)
      self->safeSetState(threadState);
    else 
      self->setState(threadState);
  }

  return result;
}

bool Condition::safeEternalWait(const Mutex& mutex) const {
  bool result = true;

  result = !pthread_cond_wait(&identifier, &mutex.identifier);
  if (result && mutex.numLocks)
    result = mutex.safeEternalWait(mutex);

  return result;
}

bool Condition::safeWaitUntil(const Mutex& mutex, const Timestamp& time) 
  const {
  bool result = true;
  timespec abstime = time;

  result = !pthread_cond_timedwait(&identifier, &mutex.identifier, &abstime);
  if (result && mutex.numLocks)
    result = mutex.safeWaitUntil(mutex, time);

  return result;
}
