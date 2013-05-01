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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file Geo.h
    \brief This file defines the Geo namespace which contains useful function
           for geodesic applications.
  */

#ifndef GEO_H
#define GEO_H

#include <Eigen/Core>

#include "base/Singleton.h"
#include "base/Serializable.h"

/** The Geo namespace contains useful functions for the Applanix.
    \brief Utilities for the Applanix.
  */
namespace Geo {
  /** \name Types definitions
    @{
    */
  /** The class R_ENU_NED contains rotation from ENU to NED and vice versa
      \brief Rotation between ENU and NED
    */
  class R_ENU_NED :
    public Singleton<R_ENU_NED>,
    public virtual Serializable {
  public:
    /** \name Constructors/destructor
      @{
      */
    /// Default constructor
    R_ENU_NED();
    /// Destructor
    virtual ~R_ENU_NED();
    /** @}
      */

    /** \name Accessors
      @{
      */
    /// Returns the raw matrix
    const Eigen::Matrix3d& getMatrix() const;
    /** @}
      */

    /** \name Operators
      @{
      */
    /// Right multiplication: R_ENU_NED * R
    Eigen::Matrix3d operator * (const Eigen::Matrix3d& R);
    /// Multiplication with itself
    Eigen::Matrix3d operator * (const R_ENU_NED& R);
    /// Right multiplication: R_ENU_NED * v
    Eigen::Vector3d operator * (const Eigen::Vector3d& v);
    /** @}
      */

    /** \name Methods
      @{
      */
    /// Left multiplication: R * R_ENU_NED
    Eigen::Matrix3d leftMultiply(const Eigen::Matrix3d& R) const;
    /** @}
      */

  protected:
    /** \name Stream methods
      @{
      */
    /// Reads from standard input
    virtual void read(std::istream& stream);
    /// Writes to standard output
    virtual void write(std::ostream& stream) const;
    /// Reads from a file
    virtual void read(std::ifstream& stream);
    /// Writes to a file
    virtual void write(std::ofstream& stream) const;
    /** @}
      */

    /** \name Protected members
      @{
      */
    /// Rotation matrix
    Eigen::Matrix3d mR;
    /** @}
      */

  };
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Left multiplication: R * R_ENU_NED
  Eigen::Matrix3d operator * (const Eigen::Matrix3d& R, const R_ENU_NED& R_ENU);
  /** @}
    */

  /** \name Constants
    @{
    */
  /// Semi-major axis WGS84 [m]
  const double aWGS84 = 6378137;
  /// Semi-minor axis WGS84 [m]
  const double bWGS84 = 6356752.314245;
  /// Semi-major axis GRS80 [m]
  const double aGRS80 = 6378137;
  /// Semi-minor axis GRS80 [m]
  const double bGRS80 = 6356752.314140;
  /// Semi-major axis Bessel1841 [m]
  const double aBessel1841 = 6377397.155;
  /// Semi-minor axis Bessel1841 [m]
  const double bBessel1841 = 6356078.962822;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Converts LLA to ECEF, lat./long. in deg.
  void llaToEcef(double latitude, double longitude, double altitude,
    double& x, double& y, double& z);
  /// Converts ECEF to LLA, lat./long. in deg.
  void ecefToLla(double& latitude, double& longitude, double& altitude,
    double x, double y, double z);
  /// Converts WGS84 to ECEF, lat./long. in deg.
  void wgs84ToEcef(double latitude, double longitude, double altitude,
    double& x, double& y, double& z);
  /// Converts ECEF to WGS84, lat./long. in deg.
  void ecefToWgs84(double& latitude, double& longitude, double& altitude,
    double x, double y, double z);
  /// Converts ECEF to NED
  void ecefToNed(double xe, double ye, double ze, double latRef, double longRef,
    double altRef, double& xn, double& yn, double& zn);
  /// Converts NED to ECEF
  void nedToEcef(double& xe, double& ye, double& ze, double latRef,
    double longRef, double altRef, double xn, double yn, double zn);
  /// Converts ECEF to ENU
  void ecefToEnu(double xe, double ye, double ze, double latRef, double longRef,
    double altRef, double& xn, double& yn, double& zn);
  /// Converts ENU to ECEF
  void enuToEcef(double& xe, double& ye, double& ze, double latRef,
    double longRef, double altRef, double xn, double yn, double zn);
  /// Converts WGS84 to LV03 (approximative), lat./long. in deg.
  void wgs84ToLv03Approx(double latitude, double longitude, double altitude,
    double& east, double& north, double& height);
  /// Converts LV03 to WGS84 (approximative), lat./long. in deg.
  void lv03ToWgs84Approx(double& latitude, double& longitude, double& altitude,
    double east, double north, double height);
  /// Converts WGS84 to LV03 (rigorous), lat./long. in deg.
  void wgs84ToLv03Rigorous(double latitude, double longitude, double altitude,
    double& east, double& north, double& height);
  /** @}
    */

};

#endif // GEO_H
