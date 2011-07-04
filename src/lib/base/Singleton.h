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

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/** Singleton type template
  * @author Ralf Kaestner SU Computer Science Dept.
  */

#include "exceptiontype.hpp"

template <class C> class Singleton :
  public ClassType<C> {
public:
  /** Types and non-static subclasses
    */
  class BadInstantiation :
    public ExceptionType<BadInstantiation> {
  public:
    /** Constructors
      */
    BadInstantiation();
  };

  /** Access the static instance
    */
  static C& getInstance();

  /** Singleton queries
    */
  static bool exists();
protected:
  static C* instance;

  /** Constructors
    */
  Singleton();

  /** Destructor
    */
  virtual ~Singleton();
};

#include "singleton.tpp"

#endif
