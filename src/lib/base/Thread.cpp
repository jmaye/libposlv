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

#include "base/Thread.h"

#include "base/Threads.h"

#ifdef __NR_gettid
static pid_t gettid (void) {
  return syscall(__NR_gettid);
}
#else
static pid_t gettid (void) {
  return -ENOSYS;
}
#endif

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <> EnumeratableType<Thread::State>::Range::Range() {
  (*this)[Thread::initialized] = "initialized";
  (*this)[Thread::starting] = "starting";
  (*this)[Thread::running] = "running";
  (*this)[Thread::sleeping] = "sleeping";
  (*this)[Thread::waiting] = "waiting";
  (*this)[Thread::interrupting] = "interrupting";
  (*this)[Thread::interrupted] = "interrupted";
  (*this)[Thread::finished] = "finished";
}

template <> EnumeratableType<Thread::Priority>::Range::Range() {
  (*this)[Thread::inherit] = "inherit";
  (*this)[Thread::idle] = "idle";
  (*this)[Thread::lowest] = "lowest";
  (*this)[Thread::low] = "low";
  (*this)[Thread::normal] = "normal";
  (*this)[Thread::high] = "high";
  (*this)[Thread::highest] = "highest";
  (*this)[Thread::critical] = "critical";
}

Thread::Identifier::Identifier(pthread_t posix) :
  posix(posix),
  kernel(-1),
  process(-1) {
}

Thread::Identifier::~Identifier() {
}

Thread::BadStackSize::BadStackSize() :
  Exception("Bad thread stack size") {
}

Thread::BadWait::BadWait() :
  Exception("Bad thread wait") {
}

Thread::Thread (double cycle, size_t stackSize) :
  state(initialized),
  cancel(false),
  priority(inherit),
  stackSize(stackSize),
  cycle(cycle),
  numCycles(0) {
}

Thread::~Thread() {
  interrupt();
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

Thread::Identifier Thread::getIdentifier() const {
  Mutex::ScopedLock lock(mutex);
  return this->identifier;
}

Thread::State Thread::getState() const {
  Mutex::ScopedLock lock(mutex);
  return this->state;
}

Thread::State Thread::setState(State state) {
  Mutex::ScopedLock lock(mutex);
  return safeSetState(state);
}

Thread::State Thread::safeSetState(State state) {
  State oldState = this->state;

  if (cancel && (state == running))
    this->state = interrupting;
  else
    this->state = state;

  return oldState;
}

Thread::Priority Thread::getPriority() const {
  Mutex::ScopedLock lock(mutex);
  return this->priority;
}

void Thread::setPriority(Priority priority) {
  Mutex::ScopedLock lock(mutex);
  safeSetPriority(priority);
}

void Thread::safeSetPriority(Priority priority) {
  this->priority = priority;

  if ((identifier.posix != 0) && (priority != inherit)) {
    int policy;
    SchedulingParameter param;

    if (!pthread_getschedparam(identifier.posix, &policy, &param)) {
      int minPriority = sched_get_priority_min(policy);
      int maxPriority = sched_get_priority_max(policy);

      if ((minPriority != -1) && (maxPriority != -1)) {
        param.sched_priority = minPriority+
          round((maxPriority-minPriority)/critical*priority);

        pthread_setschedparam(identifier.posix, policy, &param);
      }
    }
  }
}

size_t Thread::getStackSize() const {
  return stackSize;
}

double Thread::getCycle() const {
  Mutex::ScopedLock lock(mutex);
  return this->cycle;
}

void Thread::setCycle(double cycle) {
  Mutex::ScopedLock lock(mutex);
  this->cycle = cycle;
}

size_t Thread::getNumCycles() const {
  Mutex::ScopedLock lock(mutex);
  return this->numCycles;
}

const Timer& Thread::getTimer() const {
  return timer;
}

Condition& Thread::getTrigger() {
  return trigger;
}

const Condition& Thread::getTrigger() const {
  return trigger;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

bool Thread::Identifier::operator==(const Identifier& identifier) const {
  return (posix == identifier.posix);
}

bool Thread::Identifier::operator!=(const Identifier& identifier) const {
  return (posix != identifier.posix);
}

bool Thread::Identifier::operator>(const Identifier& identifier) const {
  return (posix > identifier.posix);
}

bool Thread::Identifier::operator<(const Identifier& identifier) const {
  return (posix < identifier.posix);
}

Thread::Identifier::operator const void*() const {
  return (void*)posix;
}

void Thread::Identifier::reset() {
  posix = 0;
  kernel = -1;
  process = -1;
}

void Thread::Identifier::read(InputStream& stream) {
  stream >> posix;
}

void Thread::Identifier::write(OutputStream& stream) const {
  stream << posix;
}

bool Thread::start(Priority priority, double wait) {
  Mutex::ScopedLock lock(mutex);
  bool result = false;

  if (safeWait(wait)) {
    Attribute attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);

    if (stackSize) {
      if (pthread_attr_setstacksize(&attr, stackSize))
        throw BadStackSize();
    }

    numCycles = 0;
    State state = this->state;
    safeSetState(starting);

    result = !pthread_create(&identifier.posix, &attr, Thread::start, this);

    if (result) {
      started.wait(mutex);
      safeSetPriority(priority);
    }
    else safeSetState(state);

    pthread_attr_destroy(&attr);
  }

  return result;
}

bool Thread::interrupt(double wait) {
  Mutex::ScopedLock lock(mutex);
  bool result = false;

  if (safeIsBusy()) {
    cancel = true;
    if (state == running)
      safeSetState(interrupting);

    trigger.signal();

    result = safeWait(wait);
  }

  return result;
}

void Thread::exit() {
  try {
    Threads::getInstance().getSelf().interrupt(0.0);
  }
  catch (Exception& exception) {
    pthread_exit(0);
  }
}

bool Thread::wait(double seconds) const {
  Mutex::ScopedLock lock(mutex);
  return safeWait(seconds);
}

bool Thread::safeWait(double seconds) const {
  bool result = true;

  if (seconds != 0.0) {
    Thread* self = 0;
    try {
      self = &Threads::getInstance().getSelf();
    }
    catch (Exception& exception) {
      self = 0;
    }

    if (self == this)
      throw BadWait();

    if (safeIsBusy())
      result = cleaned.wait(mutex, seconds);
  }

  return result;
}

bool Thread::exists() const {
  Mutex::ScopedLock lock(mutex);
  return safeExists();
}

bool Thread::safeExists() const {
  return (identifier.posix != 0);
}

bool Thread::isBusy() const {
  Mutex::ScopedLock lock(mutex);
  return safeIsBusy();
}

bool Thread::safeIsBusy() const {
  return ((state != initialized) &&
    (state != interrupted) &&
    (state != finished));
}

bool Thread::hasBase(const TypeInfo& type) const {
  return Type<Thread>::hasBase<Class>(type);
}

void* Thread::run() {
  initialize();

  mutex.lock();
  while (!cancel || !numCycles) {
    mutex.unlock();
    timer.start();

    process();

    mutex.lock();
    trigger.wait(mutex, timer.getLeft(cycle));
    mutex.unlock();

    timer.stop();
    mutex.lock();

    ++numCycles;
    if (cycle <= 0.0) break;
  }
  mutex.unlock();

  cleanup();
  return 0;
}

void Thread::initialize() {
  Mutex::ScopedLock lock(mutex);

  identifier.process = getpid();
  identifier.kernel = gettid();

  Threads::getInstance().registerThread(*this);

  safeSetState(running);
  started.signal(Condition::broadcast);
}

void Thread::cleanup() {
  Mutex::ScopedLock lock(mutex);

  if (cancel) safeSetState(interrupted);
  else safeSetState(finished);
  cancel = false;

  Threads::getInstance().unregisterThread(*this);
  pthread_detach(identifier.posix);

  identifier.reset();
  cleaned.signal(Condition::broadcast);
}

void* Thread::start(void* thread) {
  return ((Thread*)thread)->run();
}
