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

#include <Eigen/Array>

#include "exceptions/OutOfBoundException.h"
#include "exceptions/BadArgumentException.h"
#include "base/BinaryStreamReader.h"
#include "base/BinaryStreamWriter.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MapGrid::MapGrid(const Coordinate& minimum, const Coordinate& maximum, const
    Coordinate& resolution) :
    Grid<double, std::string, 2>(minimum, maximum, resolution) {
}

MapGrid::MapGrid(const MapGrid& other) :
    Grid<double, std::string, 2>(other) {
}

MapGrid& MapGrid::operator = (const MapGrid& other) {
  if (this != &other) {
    Grid<double, std::string, 2>::operator=(other);
  }
  return *this;
}

MapGrid::~MapGrid() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void MapGrid::writeBinary(std::ostream& stream) const {
  BinaryStreamWriter<std::ostream> streamWriter(stream);
  for (auto it = getCellBegin(); it != getCellEnd(); ++it) {
    streamWriter << it->size();
    streamWriter.write(it->c_str(), it->size());
  }
  streamWriter << mMinimum(0) << mMinimum(1) << mMaximum(0) << mMaximum(1)
    << mResolution(0) << mResolution(1) << mNumCells(0) << mNumCells(1)
    << mNumCellsTot << mLinProd(0) << mLinProd(1);
}

void MapGrid::readBinary(std::istream& stream) {
  BinaryStreamReader<std::istream> streamReader(stream);
  for (auto it = getCellBegin(); it != getCellEnd(); ++it) {
    size_t size;
    streamReader >> size;
    char buffer[size];
    streamReader.read(buffer, size);
    *it = std::string(buffer, size);
  }
}
