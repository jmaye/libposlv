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

#include "visualization/Led.h"

#include <QtGui/QBitmap>
#include <QtGui/QPainter>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Led::Led(QWidget* parent) :
  QWidget(parent) {
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
}

Led::Led(const QColor& color, QWidget* parent) :
  QWidget(parent) {
  setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
  setColor(color);
}

Led::~Led() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

QPoint Led::getCenter() const {
  return QPoint(width() / 2, height() / 2);
}

int Led::getRadius() const {
  int diameter = std::min(width(), height()) - 1;
  return diameter / 2;
}

void Led::setColor(const QColor& color) {
  QPalette palette;
  palette.setColor(backgroundRole(), color);

  setPalette(palette);
}

const QColor& Led::getColor() const {
  return palette().color(backgroundRole());
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

QSize Led::sizeHint() const {
  return QSize(fontMetrics().height(), fontMetrics().height());
}

void Led::updateMask() {
  QBitmap mask(width(), height());
  QPainter painter;

  painter.begin(&mask);
  painter.setBrush(Qt::color1);
  painter.drawEllipse(getCenter(), getRadius(), getRadius());
  painter.end();

  setMask(mask);
}

void Led::paintEvent(QPaintEvent* paintEvent) {
  QPainter painter;
  painter.begin(this);

  QColor backgroundColor(palette().color(backgroundRole()));
  int color[3] = {backgroundColor.red(), backgroundColor.green(),
    backgroundColor.blue()};
  int radius = getRadius();
  int diameter = radius * 2;

  double r, a, x, y, z;
  double phong;
  unsigned int pixels[diameter * diameter];

  for (int i = 0; i < diameter; i++) {
    int offset = i * diameter;

    for (int j = 0; j < diameter; j++) {
      r = sqrt((double)((radius - j) * (radius - j) + (radius - i) *
        (radius - i)));

      if (r <= radius) {
        x = radius - j;
        y = radius - i;
        z = sqrt(double(radius * radius - x * x - y * y));

        a = (x + y + 4.0 * z) / (sqrt(x * x + y * y + z * z) * sqrt(18.0));
        phong = std::max(0.8, a * a);

        pixels[offset + j] = (255 << 24) |
          ((int)(color[0] * phong) << 16) |
          ((int)(color[1] * phong) << 8) |
          (int)(color[2] * phong);
      }
      else pixels[offset + j] = 0;
    }
  }

  QImage image((uchar*)pixels, diameter, diameter, QImage::Format_ARGB32);

  painter.drawImage(getCenter() - QPoint(radius, radius), image);
  painter.drawEllipse(getCenter(), radius, radius);

  painter.end();
}

bool Led::event(QEvent* event) {
  if (event->type() == QEvent::Resize)
    updateMask();

  QWidget::event(event);
}
