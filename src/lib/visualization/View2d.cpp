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

#include "visualization/View2d.h"

#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QResizeEvent>

#include <iostream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

View2d::View2d(QWidget* parent) :
    QGraphicsView(parent),
    mTranslation(2, 0.0),
    mRotation(0.0),
    mScale(1.0) {
  setScene(&mScene);
  setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
  setResizeAnchor(QGraphicsView::AnchorUnderMouse);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

View2d::~View2d() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

Scene2d& View2d::getScene() {
  return mScene;
}

const Scene2d& View2d::getScene() const {
  return mScene;
}

void View2d::setTranslation(double x, double y) {
  if ((x != mTranslation[0]) || (y != mTranslation[1])) {
    mTranslation[0] = x;
    mTranslation[1] = y;
    updateTransform();
    emit translationChanged(mTranslation);
  }
}

const std::vector<double>& View2d::getTranslation() const {
  return mTranslation;
}

void View2d::setRotation(double yaw) {
  if (yaw != mRotation) {
    mRotation = yaw;
    updateTransform();
    emit rotationChanged(mRotation);
  }
}

double View2d::getRotation() const {
  return mRotation;
}

void View2d::setScale(double scale) {
  if (mScale != scale) {
    mScale = scale;
    updateTransform();
    emit scaleChanged(mScale);
  }
}

double View2d::getScale() const {
  return mScale;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void View2d::mousePressEvent(QMouseEvent* event) {
  mLastPanPoint = event->pos();
  setCursor(Qt::ClosedHandCursor);
}

void View2d::mouseReleaseEvent(QMouseEvent* event) {
  setCursor(Qt::OpenHandCursor);
  mLastPanPoint = QPoint();
}

void View2d::mouseMoveEvent(QMouseEvent* event) {
  if (!mLastPanPoint.isNull()) {
    QPointF delta = mapToScene(mLastPanPoint) - mapToScene(event->pos());
    mLastPanPoint = event->pos();
    setCenter(getCenter() + delta);
  }
}

void View2d::wheelEvent(QWheelEvent* event) {
  double deltaScale = 1e-2;
  setScale(mScale * (1.0 + deltaScale * event->delta() / 8.0));
}

void View2d::resizeEvent(QResizeEvent* event) {
  QGraphicsView::resizeEvent(event);
  emit resized();
}

void View2d::paintEvent(QPaintEvent* event) {
  QGraphicsView::paintEvent(event);
  emit updated();
}

const QPointF& View2d::getCenter() {
  return mCurrentCenterPoint;
}

void View2d::setCenter(const QPointF& centerPoint) {
  QRectF visibleArea = mapToScene(rect()).boundingRect();
  QRectF sceneBounds = sceneRect();
  double boundX = visibleArea.width() / 2.0;
  double boundY = visibleArea.height() / 2.0;
  double boundWidth = sceneBounds.width() - 2.0 * boundX;
  double boundHeight = sceneBounds.height() - 2.0 * boundY;
  QRectF bounds(boundX, boundY, boundWidth, boundHeight);
  if (bounds.contains(centerPoint))
    mCurrentCenterPoint = centerPoint;
  else {
    if (visibleArea.contains(sceneBounds)) {
      mCurrentCenterPoint = sceneBounds.center();
    }
    else {
      mCurrentCenterPoint = centerPoint;
      if (centerPoint.x() > bounds.x() + bounds.width()) {
        mCurrentCenterPoint.setX(bounds.x() + bounds.width());
      }
      else if (centerPoint.x() < bounds.x()) {
        mCurrentCenterPoint.setX(bounds.x());
      }
      if (centerPoint.y() > bounds.y() + bounds.height()) {
        mCurrentCenterPoint.setY(bounds.y() + bounds.height());
      } else if (centerPoint.y() < bounds.y()) {
        mCurrentCenterPoint.setY(bounds.y());
      }
    }
  }
  centerOn(mCurrentCenterPoint);
}

void View2d::updateTransform() {
  QTransform transform;
  transform.rotate(mRotation);
  transform.translate(mTranslation[0], mTranslation[1]);
  transform.scale(mScale, mScale);
  setTransform(transform);
}
