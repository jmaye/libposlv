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

/** \file GroupCreationException.h
    \brief This file defines the GroupCreationException class, which represents
           exception in the group creation
  */

#ifndef GROUPCREATIONEXCEPTION_H
#define GROUPCREATIONEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class GroupCreationException represents exception in the group creation.
    \brief Group creation exception
  */
class GroupCreationException :
  public std::range_error {
  /** \name Private constructors
    @{
    */
  /// Assignment operator
  GroupCreationException& operator = (const GroupCreationException& other);
  /** @}
    */

public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs exception from message
  GroupCreationException(const std::string& msg = "");
  /// Copy constructor
  GroupCreationException(const GroupCreationException& other);
  /** @}
    */

protected:

};

#endif // GROUPCREATIONEXCEPTION_H
