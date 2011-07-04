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

#ifndef CONDITION_HPP
#define CONDITION_HPP

/** Thread condition class
  * @author Ralf Kaestner SU Computer Science Dept.
  */

#include "timer.hpp"

#include "enumeratabletype.hpp"

class Mutex;

class Condition :
  public virtual Class,
  public ClassType<Condition> {
public:
  /** Types and non-static subclasses
    */
  enum SignalType {
    unicast,
    broadcast
  };

  /** Constructors
    */
  Condition();
  /** Destructor
    */
  virtual ~Condition();

  /** Signal the condition
    */
  void signal(SignalType signalType = unicast);

  /** Wait for the condition to be signaled
    */
  bool wait(Mutex& mutex, double seconds = Timer::eternal()) const;

  virtual bool hasBase(const TypeInfo& type) const;
protected:
  mutable pthread_cond_t identifier;

  /** Safely wait for the condition to be signaled
    */
  bool safeWait(const Mutex& mutex, double seconds) const;

  /** Safely wait eternally for the condition to be signaled
    */
  bool safeEternalWait(const Mutex& mutex) const;
  /** Safely wait until the specified time for the condition to be signaled
    */
  bool safeWaitUntil(const Mutex& mutex, const Timestamp& time) const;
};

#endif
