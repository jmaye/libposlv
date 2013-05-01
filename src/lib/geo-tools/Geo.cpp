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

#include "geo-tools/Geo.h"

#include <cmath>

#include "sensor/Utils.h"

namespace Geo {

/******************************************************************************/
/* Constructors                                                               */
/******************************************************************************/

R_ENU_NED::R_ENU_NED() {
  mR << 0, 1, 0, 1, 0, 0, 0, 0, -1;
}

R_ENU_NED::~R_ENU_NED() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void R_ENU_NED::read(std::istream& stream) {
}

void R_ENU_NED::write(std::ostream& stream) const {
  stream << mR;
}

void R_ENU_NED::read(std::ifstream& stream) {
}

void R_ENU_NED::write(std::ofstream& stream) const {
  stream << mR;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const Eigen::Matrix3d& R_ENU_NED::getMatrix() const {
  return mR;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Eigen::Matrix3d R_ENU_NED::operator * (const Eigen::Matrix3d& R) {
  return mR * R;
}

Eigen::Matrix3d R_ENU_NED::operator * (const R_ENU_NED& R) {
  return mR * R.mR;
}

Eigen::Matrix3d R_ENU_NED::leftMultiply(const Eigen::Matrix3d& R) const {
  return R * mR;
}

Eigen::Vector3d R_ENU_NED::operator * (const Eigen::Vector3d& v) {
  return mR * v;
}

Eigen::Matrix3d operator * (const Eigen::Matrix3d& R, const R_ENU_NED& R_ENU) {
  return R_ENU.leftMultiply(R);
}

void llaToEcef(double latitude, double longitude, double altitude,
    double& x, double& y, double& z, double a, double b) {
  const double slat = sin(Utils::deg2rad(latitude));
  const double clat = cos(Utils::deg2rad(latitude));
  const double slong = sin(Utils::deg2rad(longitude));
  const double clong = cos(Utils::deg2rad(longitude));
  const double e2 = (a * a - b * b) / (a * a);
  const double R = a / std::sqrt(1 - e2 * slat * slat);
  x = (R + altitude) * clat * clong;
  y = (R + altitude) * clat * slong;
  z = (R * (1 - e2) + altitude) * slat;
}

void ecefToLla(double& latitude, double& longitude, double& altitude,
    double x, double y, double z, double a, double b) {
  const double e2 = (a * a - b * b) / (a * a);
  const double ep2 = (a * a - b * b) / (b * b);
  const double r = std::sqrt(x * x + y * y);
  const double F = 54 * b * b * z * z;
  const double G = r * r + (1 - e2) * z * z - e2 * (a * a - b * b);
  const double c = e2 * e2 * F * r * r / std::pow(G, 3);
  const double s = std::cbrt(1 + c + std::sqrt(c * c + 2 * c));
  const double P = F / (3 * (s + 1 / s + 1) * (s + 1 / s + 1) * G * G);
  const double Q = std::sqrt(1 + 2 * e2 * e2 * P);
  const double r0 = -e2 * P * r / (1 + Q) +
    std::sqrt(0.5 * a * a * (1 + 1 / Q) - ((1 - e2) *
    P * z * z) / (Q * (1 + Q)) - P * r * r / 2);
  const double U = std::sqrt((r - e2 * r0) * (r - e2 * r0) + z * z);
  const double V = std::sqrt((r - e2 * r0) * (r - e2 * r0) + (1 - e2) * z * z);
  const double z0 = b * b * z / a / V;
  const double phi = atan((z + ep2 * z0) / r);
  const double lambda = atan2(y, x);
  const double h = U * (1 - b * b / a / V);
  latitude = Utils::rad2deg(phi);
  longitude = Utils::rad2deg(lambda);
  altitude = h;
}

void wgs84ToEcef(double latitude, double longitude, double altitude,
    double& x, double& y, double& z) {
  llaToEcef(latitude, longitude, altitude, x, y, z, aWGS84, bWGS84);
}

void ecefToWgs84(double& latitude, double& longitude, double& altitude,
    double x, double y, double z) {
  ecefToLla(latitude, longitude, altitude, x, y, z, aWGS84, bWGS84);
}

void ecefToNed(double xe, double ye, double ze, double latRef, double longRef,
    double altRef, double& xn, double& yn, double& zn) {
  const double slat = sin(Utils::deg2rad(latRef));
  const double clat = cos(Utils::deg2rad(latRef));
  const double slong = sin(Utils::deg2rad(longRef));
  const double clong = cos(Utils::deg2rad(longRef));
  Eigen::Matrix3d R;
  R << -slat * clong, -slat * slong, clat, -slong, clong, 0, -clat * clong,
    -clat * slong, -slat;
  double xref, yref, zref;
  wgs84ToEcef(latRef, longRef, altRef, xref, yref, zref);
  const Eigen::Vector3d p = R *
    (Eigen::Vector3d(xe, ye, ze) - Eigen::Vector3d(xref, yref, zref));
  xn = p(0);
  yn = p(1);
  zn = p(2);
}

void nedToEcef(double& xe, double& ye, double& ze, double latRef,
    double longRef, double altRef, double xn, double yn, double zn) {
  const double slat = sin(Utils::deg2rad(latRef));
  const double clat = cos(Utils::deg2rad(latRef));
  const double slong = sin(Utils::deg2rad(longRef));
  const double clong = cos(Utils::deg2rad(longRef));
  Eigen::Matrix3d R;
  R << -slat * clong, -slat * slong, clat, -slong, clong, 0, -clat * clong,
    -clat * slong, -slat;
  double xref, yref, zref;
  wgs84ToEcef(latRef, longRef, altRef, xref, yref, zref);
  const Eigen::Vector3d p = R.transpose() * Eigen::Vector3d(xn, yn, zn)
    + Eigen::Vector3d(xref, yref, zref);
  xe = p(0);
  ye = p(1);
  ze = p(2);
}

void ecefToEnu(double xe, double ye, double ze, double latRef, double longRef,
    double altRef, double& xn, double& yn, double& zn) {
  const double slat = sin(Utils::deg2rad(latRef));
  const double clat = cos(Utils::deg2rad(latRef));
  const double slong = sin(Utils::deg2rad(longRef));
  const double clong = cos(Utils::deg2rad(longRef));
  Eigen::Matrix3d R;
  R << -slong, clong, 0, -slat * clong, -slat * slong, clat, clat * clong,
    clat * slong, slat;
  double xref, yref, zref;
  wgs84ToEcef(latRef, longRef, altRef, xref, yref, zref);
  const Eigen::Vector3d p = R *
    (Eigen::Vector3d(xe, ye, ze) - Eigen::Vector3d(xref, yref, zref));
  xn = p(0);
  yn = p(1);
  zn = p(2);
}

void enuToEcef(double& xe, double& ye, double& ze, double latRef,
    double longRef, double altRef, double xn, double yn, double zn) {
  const double slat = sin(Utils::deg2rad(latRef));
  const double clat = cos(Utils::deg2rad(latRef));
  const double slong = sin(Utils::deg2rad(longRef));
  const double clong = cos(Utils::deg2rad(longRef));
  Eigen::Matrix3d R;
  R << -slong, clong, 0, -slat * clong, -slat * slong, clat, clat * clong,
    clat * slong, slat;
  double xref, yref, zref;
  wgs84ToEcef(latRef, longRef, altRef, xref, yref, zref);
  const Eigen::Vector3d p = R.transpose() * Eigen::Vector3d(xn, yn, zn)
    + Eigen::Vector3d(xref, yref, zref);
  xe = p(0);
  ye = p(1);
  ze = p(2);
}

void wgs84ToLv03Approx(double latitude, double longitude, double altitude,
    double& east, double& north, double& height) {
  latitude = Utils::decToSexAngle(latitude);
  longitude = Utils::decToSexAngle(longitude);
  latitude = Utils::sexAngleToSeconds(latitude);
  longitude = Utils::sexAngleToSeconds(longitude);
  double latitudeAux = (latitude - 169028.66) / 10000;
  double longitudeAux = (longitude - 26782.5) / 10000;
  east = 600072.37 + 211455.93 * longitudeAux - 10938.51 * longitudeAux *
    latitudeAux - 0.36 * longitudeAux * latitudeAux * latitudeAux
    - 44.54 * longitudeAux * longitudeAux * longitudeAux;
  north = 200147.07 + 308807.95 * latitudeAux + 3745.25 * longitudeAux *
    longitudeAux + 76.63 * latitudeAux * latitudeAux - 194.56 * longitudeAux *
    longitudeAux * latitudeAux + 119.79 * latitudeAux * latitudeAux *
    latitudeAux;
  height = altitude - 49.55 + 2.73 * longitudeAux + 6.94 * latitudeAux;
}

void lv03ToWgs84Approx(double& latitude, double& longitude, double& altitude,
    double east, double north, double height) {
  double eastAux = (east - 600000) / 1000000;
  double northAux = (north - 200000) / 1000000;
  longitude = 2.6779094 + 4.728982 * eastAux + 0.791484 * eastAux * northAux +
    0.1306 * eastAux * northAux * northAux - 0.0436 * eastAux * eastAux *
    eastAux;
  longitude = longitude * 100 / 36;
  latitude = 16.9023892 + 3.238272 * northAux - 0.270978 * eastAux * eastAux
    - 0.002528 * northAux * northAux - 0.0447 * eastAux * eastAux * northAux
    - 0.0140 * northAux * northAux * northAux;
  latitude = latitude * 100 / 36;
  altitude = height + 49.55 - 12.60 * eastAux - 22.64 * northAux;
}

void wgs84ToLv03Rigorous(double latitude, double longitude, double altitude,
    double& east, double& north, double& height) {
  const double a = aBessel1841;
  const double b = bBessel1841;
  const double E2 = (a * a - b * b) / (a * a);
  const double E = std::sqrt(E2);
  const double phi0 = Utils::deg2rad(46.95240555555556);
  const double sphi0 = sin(phi0);
  const double cphi0 = cos(phi0);
  const double lambda0 = Utils::deg2rad(7.439583333333333);
  const double R = a * std::sqrt(1 - E2) / (1 - E2 * sphi0 * sphi0);
  const double alpha = std::sqrt(1 + E2 / (1 - E2) * std::pow(cphi0, 4));
  const double b0 = asin(sphi0 / alpha);
  const double K = std::log(tan(M_PI / 4.0 + b0 * 0.5)) -
    alpha * std::log(tan(M_PI / 4.0 + phi0 * 0.5)) +
    alpha * E * 0.5 * std::log((1 + E * sphi0) / (1 - E * sphi0));
  double xecef, yecef, zecef;
  wgs84ToEcef(latitude, longitude, altitude, xecef, yecef, zecef);
  xecef -= 674.374;
  yecef -= 15.056;
  zecef -= 405.346;
  double lat03, long03, alt03;
  ecefToLla(lat03, long03, alt03, xecef, yecef, zecef, a, b);
  const double phi = Utils::deg2rad(lat03);
  const double lambda = Utils::deg2rad(long03);
  const double sphi = sin(phi);
  const double S = alpha * std::log(tan(M_PI / 4.0 + phi * 0.5)) -
    alpha * E * 0.5 * std::log((1 + E * sphi) / (1 - E * sphi)) + K;
  const double bs = 2 * (atan(exp(S)) - M_PI / 4.0);
  const double I = alpha * (lambda - lambda0);
  const double Ib = atan(sin(I) / (sin(b0) * tan(bs) + cos(b0) * cos(I)));
  const double bb = asin(cos(b0) * sin(bs) - sin(b0) * cos(bs) * cos(I));
  const double Y = R * Ib;
  const double X = R * 0.5 * std::log((1 + sin(bb)) / (1 - sin(bb)));
  east = Y + 600000;
  north = X + 200000;
}

}
