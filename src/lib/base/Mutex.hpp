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

#ifndef MUTEX_HPP
#define MUTEX_HPP

/** Thread mutex class
  * This class is thread-safe.
  * @author Ralf Kaestner SU Computer Science Dept.
  */

#include "condition.hpp"

#include "exceptiontype.hpp"

class Mutex :
  public virtual Class,
  protected Condition,
  public ClassType<Mutex> {
friend class Condition;
public:
  /** Types and non-static subclasses
    */
  class Deadlock :
    public ExceptionType<Deadlock> {
  public:
    /** Constructors
      */
    Deadlock();
  };

  class BadOperation :
    public ExceptionType<BadOperation> {
  public:
    /** Constructors
      */
    BadOperation();
  };

  class BadPermissions :
    public ExceptionType<BadPermissions> {
  public:
    /** Constructors
      */
    BadPermissions();
  };

  struct ScopedLock :
    public Structure,
    public StructureType<ScopedLock> {
  public:
    /** Constructors
      */
    ScopedLock(Mutex& mutex);
    /** Destructor
      */
    ~ScopedLock();
  protected:
    Pointer<Mutex> mutex;
  };

  /** Constructors
    */
  Mutex(bool recursive = false);
  /** Destructor
    */
  virtual ~Mutex();

  /** Access the number of locks of this mutex
    */
  size_t getNumLocks() const;

  /** Lock the mutex
    */
  bool lock(double wait = Timer::eternal());
  /** Unlock the mutex
    */
  void unlock();

  /** Try to lock the mutex without blocking the calling thread
    */
  bool tryLock();

  /** Wait for the mutex to unlock
    */
  bool waitUnlock(double seconds = Timer::eternal()) const;

  /** Mutex queries
    */
  bool isRecursive() const;
  bool isLocked() const;

  virtual bool hasBase(const TypeInfo& type) const;
protected:
  bool recursive;
  size_t numLocks;

  mutable pthread_mutex_t identifier;
  pthread_t owner;

  /** Safely lock and unlock the mutex
    */
  virtual bool safeLock(double wait);
  virtual void safeUnlock();

  bool safeEternalWait(const Mutex& mutex) const;
  bool safeWaitUntil(const Mutex& mutex, const Timestamp& time) const;
};

#endif
