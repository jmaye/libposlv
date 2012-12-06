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

/** \file Path3DTab.h
    \brief This file defines the Path3DTab class which is the control
           for the 3D displaying of a path
  */

#ifndef PATH3DTAB_H
#define PATH3DTAB_H

#include <vector>

#include <QtGui/QColor>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/View3d.h"
#include "visualization/Scene3d.h"
#include "data-structures/PointCloud.h"

class Ui_Path3DTab;

/** The Path3DTab class is the control for displaying a 3D path.
    \brief 3D path display
  */
class Path3DTab :
  public Control,
  public Singleton<Path3DTab> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Path3DTab(const Path3DTab& other);
  /// Assignment operator
  Path3DTab& operator = (const Path3DTab& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Path3DTab();
  /// Destructor
  virtual ~Path3DTab();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the points color
  void setPointColor(const QColor& color);
  /// Sets the points size
  void setPointSize(double size);
  /// Shows the points
  void setShowPoints(bool showPoints);
  /// Smoothes the points
  void setSmoothPoints(bool smoothPoints);
  /// Sets the background color
  void setBackgroundColor(const QColor& color);
  /// Sets the fog color
  void setFogColor(const QColor& color);
  /// Sets the ground color
  void setGroundColor(const QColor& color);
  /// Sets the path
  void setPath(const PointCloud<>& path);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the points
  void renderPoints(double size, bool smooth);
  /// Render background
  void renderBackground();
  /// Render fog
  void renderFog(double start, double end, double density);
  /// Render axes
  void renderAxes(double length);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Pointer to the UI
  Ui_Path3DTab* mUi;
  /// Palette
  Palette mPalette;
  /// Point cloud to render
  PointCloud<> mPointCloud;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Render the scene
  void render(View3d& view, Scene3d& scene);
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Point size changed
  void pointSizeChanged(double pointSize);
  /// Smooth points toggled
  void smoothPointsToggled(bool checked);
  /** @}
    */

};

#endif // PATH3DTAB_H
