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

#ifndef TIMER_HPP
#define TIMER_HPP

/** Timer class
  * @author Ralf Kaestner SU Computer Science Dept.
  */

#include "class.hpp"

#include "timestamp.hpp"

class Timer :
  public virtual Class,
  public ClassType<Timer> {
public:
  /** Constructors
    */
  Timer(bool start = false);
  Timer(const Timer& src);
  /** Destructor
    */
  virtual ~Timer();

  /** Access the timer's measured period in seconds
    */
  double getPeriod() const;
  /** Access the timer's measured frequency (equals 1.0/period)
    */
  double getFrequency() const;
  /** Access the timer's start time
    */
  const Timestamp& getStartTime() const;
  /** Access the timer's time left for the specified period in seconds
    */
  double getLeft(double period) const;

  /** Timer assignments
    */
  Timer& assign(const Timer& src);

  Timer& operator=(const Timer& src);

  /** Start the timer
    */
  void start(bool reset = true);
  /** Stop the time after the specified period has elapsed
    */
  void stop(double period = 0.0);
  /** Reset the timer
    */
  void reset();

  /** Wait for the specified period to elapse, but do not stop the timer
    */
  void wait(double period) const;

  /** Sleep the specified period in seconds
    */
  static void sleep(double period);

  /** Return a numeric value for an infinite period of time
    */
  static double eternal();

  virtual void read(InputStream& stream);
  virtual void write(OutputStream& stream) const;

  virtual bool hasBase(const TypeInfo& type) const;
protected:
  Timestamp startTime;
  double period;
};

#endif
