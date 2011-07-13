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

/** \file Led.h
    \brief This file defines the Led class which is a QWidget Led
  */

#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QEvent>

/** The Led class is a QWidget Led.
    \brief QWidget for Led
  */
class Led :
  public QWidget {
Q_OBJECT
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs a Led object with given parent
  Led(QWidget* parent = 0);
  /// Constructs a Led object with given color
  Led(const QColor& color, QWidget* parent = 0);
  /// Destructor
  virtual ~Led();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the LED's center
  QPoint getCenter() const;
  /// Access the LED's radius
  int getRadius() const;
  /// Sets the LED's color
  void setColor(const QColor& color);
  /// Returns the LED's color
  const QColor& getColor() const;
  /// Returns the size hint
  virtual QSize sizeHint() const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Update the LED's mask bitmap
  void updateMask();
  // Paint event
  virtual void paintEvent(QPaintEvent* paintEvent);
  // Event
  virtual bool event(QEvent* event);
  /** @}
    */

};

#endif // LED_H
