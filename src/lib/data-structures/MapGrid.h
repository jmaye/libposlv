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

/** \file MapGrid.h
    \brief This file defines the MapGrid class, which represents a map grid.
  */

#ifndef MAPGRID_H
#define MAPGRID_H

#include <string>

#include "data-structures/Grid.h"

/** The class MapGrid represents a map grid.
    \brief Map grid
  */
class MapGrid :
  public Grid<double, std::string, 2> {
public:
  /** \name Types definitions
    @{
    */
//  /// Container type
//  typedef std::vector<C> Container;
//  /// Constant iterator type
//  typedef typename Container::const_iterator ConstCellIterator;
//  /// Iterator type
//  typedef typename Container::iterator CellIterator;
//  /// Index type
//  typedef Eigen::Matrix<size_t, M, 1> Index;
//  /// Coordinate type
//  typedef Eigen::Matrix<T, M, 1> Coordinate;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs MapGrid with parameters
  MapGrid(const Coordinate& minimum, const Coordinate& maximum, const
    Coordinate& resolution);
  /// Copy constructor
  MapGrid(const MapGrid& other);
  /// Assignment operator
  MapGrid& operator = (const MapGrid& other);
  /// Destructor
  virtual ~MapGrid();
  /** @}
    */

  /** \name Stream methods
    @{
    */
  /// Stream the MapGrid into binary format
  virtual void writeBinary(std::ostream& stream) const;
  /// Reads the MapGrid from a binary format
  virtual void readBinary(std::istream& stream);
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
//  /// Reads from standard input
//  virtual void read(std::istream& stream);
//  /// Writes to standard output
//  virtual void write(std::ostream& stream) const;
//  /// Reads from a file
//  virtual void read(std::ifstream& stream);
//  /// Writes to a file
//  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
      @{
    */
//  /// Cell container
//  Container mCells;
//  /// Minimum coordinate of the MapGrid
//  Coordinate mMinimum;
//  /// Maximum coordinate of the MapGrid
//  Coordinate mMaximum;
//  /// Resolution of the MapGrid
//  Coordinate mResolution;
//  /// Number of cells in each dimension
//  Index mNumCells;
//  /// Total number of cells
//  size_t mNumCellsTot;
//  /// Pre-computation for linear indices
//  Index mLinProd;
  /** @}
    */

};

#include "data-structures/MapGrid.tpp"

#endif // MAPGRID_H
