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

#include "sensor/Checksum.h"

namespace Checksum {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

uint16_t getSum(const char* buffer, size_t size) {
  size_t size16 = size / 2;
  const uint16_t* buffer16 = reinterpret_cast<const uint16_t*>(buffer);
  uint16_t sum = 0;
  for (size_t i = 0; i < size16; ++i)
    sum += buffer16[i];
  return sum;
}

}
