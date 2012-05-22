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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Checksum.h
    \brief This file defines the Checksum namespace which contains utilities
           for checksum computation.
  */

#ifndef CHECKSUM_H
#define CHECKSUM_H

#include <stdint.h>
#include <cstdlib>

/** The Checksum namespace contains utilities for checksum computation.
    \brief Checksum utilities
  */
namespace Checksum {
  /** \name Methods
    @{
    */
  /// Returns the sum of byte pairs cast as short (16 bit) integer
  uint16_t getSum(const char* buffer, size_t size);
  /** @}
    */

};

#endif // CHECKSUM_H
