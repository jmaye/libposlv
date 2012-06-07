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

/** \file Scene2d.h
    \brief This file contains a 2d scene implementation
  */

#ifndef SCENE2D_H
#define SCENE2D_H

#include <QtGui/QGraphicsScene>

/** The Scene2d class represents a 2d scene.
    \brief 2d scene
  */
class Scene2d :
  public QGraphicsScene {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Scene2d(const Scene2d& other);
  /// Assignment operator
  Scene2d& operator = (const Scene2d& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the scene
  Scene2d(QObject* parent = 0);
  /// Destructor
  virtual ~Scene2d();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /** @}
    */

  /** \name Methods
    @{
    */
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /** @}
    */

  /** \name Protected members
    @{
    */
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /** @}
    */

};

#endif // SCENE2D_H
