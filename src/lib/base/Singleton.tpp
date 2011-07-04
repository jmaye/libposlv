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

#include "singletons.hpp"

/*****************************************************************************/
/* Statics                                                                   */
/*****************************************************************************/

template <class C> C* Singleton<C>::instance = 0;

/*****************************************************************************/
/* Constructors and Destructor                                               */
/*****************************************************************************/

template <class C>
Singleton<C>::BadInstantiation::BadInstantiation() :
  Exception("Bad singleton instantiation") {
}

template <class C>
Singleton<C>::Singleton() {
  if (instance)
    throw BadInstantiation();

  instance = (C*)this;
  Singletons::registerSingleton(*instance);
}

template <class C>
Singleton<C>::~Singleton() {
  Singletons::unregisterSingleton(*instance);
  instance = 0;
}

/*****************************************************************************/
/* Accessors                                                                 */
/*****************************************************************************/

template <class C>
C& Singleton<C>::getInstance() {
  if (!instance)
    new C();

  return *instance;
}

/*****************************************************************************/
/* Methods                                                                   */
/*****************************************************************************/

template <class C>
bool Singleton<C>::exists() {
  return instance;
}
