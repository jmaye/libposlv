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

/** \file PathBuilder.h
    \brief This file defines the PathBuilder class which builds a path in Swiss
           coordinates.
  */

#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <memory>
#include <vector>
#include <string>

#include <Eigen/Core>

#include <QtCore/QObject>

class Packet;

/** The PathBuilder class builds a path in Swiss coordinates from Applanix
    data.
    \brief Path builder
  */
class PathBuilder :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PathBuilder(const PathBuilder& other);
  /// Assignment operator
  PathBuilder& operator = (const PathBuilder& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  PathBuilder(bool dump = true, const std::string& filename = "path.txt");
  /// Destructor
  virtual ~PathBuilder();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Data points of the path
  std::vector<Eigen::Matrix<double, 3, 1> > mPath;
  /// Dump into file when done reading
  bool mDump;
  /// Filename to dump the data
  std::string mFilename;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Packet read
  void readPacket(std::shared_ptr<Packet> packet);
  /// Start receiving a path
  void start();
  /// EOF
  void eof();
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Path ready
  void path(const std::vector<Eigen::Matrix<double, 3, 1> >& path);
  /** @}
    */

};

#endif // PATHBUILDER_H
