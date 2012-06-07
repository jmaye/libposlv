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

/** \file View2d.h
    \brief This file contains a 2d view implementation
  */

#ifndef VIEW2D_H
#define VIEW2D_H

#include <vector>

#include <QtGui/QGraphicsView>

#include "base/Singleton.h"
#include "visualization/Scene2d.h"

/** The View2d class represents a 2d view.
    \brief 2d view
  */
class View2d :
  public QGraphicsView,
  public Singleton<View2d> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  View2d(const View2d& other);
  /// Assignment operator
  View2d& operator = (const View2d& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the view
  View2d(QWidget* parent = 0);
  /// Destructor
  virtual ~View2d();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the scene
  Scene2d& getScene();
  /// Returns the scene
  const Scene2d& getScene() const;
  /// Sets the view translation
  void setTranslation(double x, double y);
  /// Returns the view translation
  const std::vector<double>& getTranslation() const;
  /// Sets the view rotation
  void setRotation(double yaw);
  /// Returns the view rotation
  double getRotation() const;
  /// Sets the view scale
  void setScale(double scale);
  /// Returns the view scale
  double getScale() const;
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
  /// Mouse press event
  virtual void mousePressEvent(QMouseEvent* event);
  /// Mouse release event
  virtual void mouseReleaseEvent(QMouseEvent* event);
  /// Mouse move event
  virtual void mouseMoveEvent(QMouseEvent* event);
  /// Mouse wheel event
  virtual void wheelEvent(QWheelEvent* event);
  /// Paint event
  virtual void paintEvent(QPaintEvent* event);
  /// Resize event
  virtual void resizeEvent(QResizeEvent* event);
  /// Sets the current centerpoint
  void setCenter(const QPointF& centerPoint);
  /// Returns the current center point
  const QPointF& getCenter();
  /// Update the transformation
  void updateTransform();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Scene
  Scene2d mScene;
  /// Holds the current centerpoint of the view, used for panning and zooming
  QPointF mCurrentCenterPoint;
  /// From panning the view
  QPoint mLastPanPoint;
  /// Translation
  std::vector<double> mTranslation;
  /// Rotation
  double mRotation;
  /// Scale
  double mScale;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Updated signal
  void updated();
  /// Resized signal
  void resized();
  /// Translation has changed
  void translationChanged(const std::vector<double>& translation);
  /// Rotation has changed
  void rotationChanged(double rotation);
  /// Scale has changed
  void scaleChanged(double scale);
  /** @}
    */

};

#endif // VIEW2D_H
