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

#ifndef THREAD_HPP
#define THREAD_HPP

/** Thread class
  * This class is thread-safe through mutual exclusion.
  * @author Ralf Kaestner SU Computer Science Dept.
  */

#include "mutex.hpp"

class Thread :
  public virtual Class,
  public ClassType<Thread> {
friend class Threads;
friend class Condition;
friend class Timer;
public:
  /** Types and non-static subclasses
    */
  typedef pthread_attr_t Attribute;
  typedef sched_param SchedulingParameter;

  enum State {
    initialized,
    starting,
    running,
    sleeping,
    waiting,
    interrupting,
    interrupted,
    finished
  };

  enum Priority {
    inherit,
    idle,
    lowest,
    low,
    normal,
    high,
    highest,
    critical
  };

  struct Identifier :
    public Structure,
    public StructureType<Identifier> {
  public:
    pthread_t posix;
    pid_t kernel;
    pid_t process;

    /** Constructors
      */
    Identifier(pthread_t posix = 0);
    /** Destructor
      */
    virtual ~Identifier();

    /** Thread identifier comparisons
      */
    bool operator==(const Identifier& identifier) const;
    bool operator!=(const Identifier& identifier) const;
    bool operator>(const Identifier& identifier) const;
    bool operator<(const Identifier& identifier) const;

    /** Thread identifier conversions
      */
    operator const void*() const;

    /** Reset the identifier
      */
    void reset();

    void read(InputStream& stream);
    void write(OutputStream& stream) const;
  };

  class BadStackSize :
    public ExceptionType<BadStackSize> {
  public:
    /** Constructors
      */
    BadStackSize();
  };

  class BadWait :
    public ExceptionType<BadWait> {
  public:
    /** Constructors
      */
    BadWait();
  };

  /** Constructors
    */
  Thread(double cycle = 0.0, size_t stackSize = 0);
  /** Destructor
    */
  virtual ~Thread();

  /** Access the thread's identifier
    */
  Identifier getIdentifier() const;
  /** Access the thread's state
    */
  State getState() const;
  /** Access the thread's priority
    */
  Priority getPriority() const;
  void setPriority(Priority priority);
  /** Access the thread's stack size
    */
  size_t getStackSize() const;
  /** Access the thread's cycle period in seconds
    */
  double getCycle() const;
  void setCycle(double cycle);
  /** Access the thread's number of cycles performed
    */
  size_t getNumCycles() const;
  /** Access the thread's timer
    */
  const Timer& getTimer() const;
  /** Access the thread's trigger
    */
  Condition& getTrigger();
  const Condition& getTrigger() const;

  /** Start the thread
    */
  bool start(Priority priority = inherit, double wait = Timer::eternal());
  /** Interrupt the thread
    * Note that a thread waiting for itself will produce a badWait
    * exception here. The only excemption from this rule is a wait period
    * of zero which causes Thread::wait() to return immediately. A thread
    * may thus interrupt itself.
    */
  bool interrupt(double wait = Timer::eternal());

  /** Exit the calling thread
    */
  static void exit();

  /** Wait until the thread has finished execution or the specified time
    * elapsed
    */
  bool wait(double seconds = Timer::eternal()) const;

  /** Thread queries
    */
  bool exists() const;
  bool isBusy() const;

  virtual bool hasBase(const TypeInfo& type) const;
protected:
  Identifier identifier;
  State state;
  bool cancel;
  Priority priority;

  size_t stackSize;
  double cycle;
  size_t numCycles;

  mutable Mutex mutex;
  Condition started;
  Condition trigger;
  Condition cleaned;

  Timer timer;

  /** Access the thread's state and returns its former state
    */
  State setState(State state);
  /** Safely access the thread's state
    */
  virtual State safeSetState(State state);
  /** Safely access the thread's priority
    */
  virtual void safeSetPriority(Priority priority);

  /** Run all thread operations
    */
  virtual void* run();

  /** Do initialization
    */
  virtual void initialize();
  /** Do computational processing
    */
  virtual void process() = 0;
  /** Do cleanup
    */
  virtual void cleanup();

  /** Safely wait until the thread has finished execution or the specified
    * time elapsed
    */
  virtual bool safeWait(double seconds) const;

  /** Safe thread queries
    */
  virtual bool safeExists() const;
  virtual bool safeIsBusy() const;

  /** Start the given thread object
    */
  static void* start(void* thread);
};

#endif
