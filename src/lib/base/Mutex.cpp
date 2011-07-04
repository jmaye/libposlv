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

#include "mutex.hpp"
#include "threads.hpp"

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

Mutex::Deadlock::Deadlock() :
  Exception("Mutex deadlock") {
}

Mutex::BadOperation::BadOperation() :
  Exception("Bad mutex operation") {
}

Mutex::BadPermissions::BadPermissions() :
  Exception("Bad mutex permissions") {
}

Mutex::ScopedLock::ScopedLock(Mutex& mutex) :
  mutex(&mutex) {
  this->mutex->lock();
}

Mutex::ScopedLock::~ScopedLock() {
  mutex->unlock();
}

Mutex::Mutex(bool recursive) :
  recursive(recursive),
  numLocks(0),
  owner(0) {
  pthread_mutex_init(&identifier, 0);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&identifier);
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

size_t Mutex::getNumLocks() const {
  pthread_mutex_lock(&identifier);

  size_t numLocks = this->numLocks;

  pthread_mutex_unlock(&identifier);
  return numLocks;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

bool Mutex::lock(double wait) {
  bool result = false;
  pthread_mutex_lock(&identifier);

  try {
    result = safeLock(wait);
  }
  catch (Exception& exception) {
    pthread_mutex_unlock(&identifier);
    throw;
  }

  pthread_mutex_unlock(&identifier);
  return result;
}

void Mutex::unlock() {
  pthread_mutex_lock(&identifier);

  try {
    safeUnlock();
  }
  catch (Exception& exception) {
    pthread_mutex_unlock(&identifier);
    throw;
  }

  pthread_mutex_unlock(&identifier);
}

bool Mutex::waitUnlock(double seconds) const {
  pthread_mutex_lock(&identifier);

  bool result = safeWait(*this, seconds);
  if (result)
    ((Mutex*)this)->signal();

  pthread_mutex_unlock(&identifier);
  return result;
}

bool Mutex::tryLock() {
  return lock(0.0);
}

bool Mutex::isRecursive() const {
  return recursive;
}

bool Mutex::isLocked() const {
  pthread_mutex_lock(&identifier);

  bool result = numLocks;

  pthread_mutex_unlock(&identifier);
  return result;
}

bool Mutex::hasBase(const TypeInfo& type) const {
  return Type<Mutex>::hasBase<Class>(type) ||
    Type<Mutex>::hasBase<Condition>(type);
}

bool Mutex::safeLock(double wait) {
  bool result = true;

  if (pthread_self() == owner) {
    if (!recursive)
      throw Deadlock();
    else
      ++numLocks;
  }
  else {
    if (numLocks)
      result = safeWait(*this, wait);

    if (result) {
      ++numLocks;
      owner = pthread_self();
    }
  }

  return result;
}

void Mutex::safeUnlock() {
  if (!numLocks)
    throw BadOperation();

  if (pthread_self() != owner)
    throw BadPermissions();

  --numLocks;
  if (!numLocks) {
    owner = 0;
    signal();
  }
}

bool Mutex::safeEternalWait(const Mutex& mutex) const {
  bool result = true;

  while (result && numLocks)
    result = !pthread_cond_wait(&(Condition::identifier), &identifier);

  return result;
}

bool Mutex::safeWaitUntil(const Mutex& mutex, const Timestamp& time) const {
  bool result = true;
  timespec abstime = time;

  while (result && numLocks)
    !pthread_cond_timedwait(&(Condition::identifier), &identifier, &abstime);

  return result;
}
