cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libposlv
  VERSION 1.0
  RELEASE beta
  SUMMARY "A C++ based Applanix POS LV interfacing library"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "https://github.com/jmaye/libposlv"
  LICENSE "GNU Lesser General Public License (LGPL)"
  PREFIX poslv-
  INSTALL /usr/
  EXTRA_CXX_FLAGS -std=c++0x
)

remake_doc(
  html
  latex
  vendor
)

remake_pack_deb(
  DESCRIPTION "Main library"
)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  DEPENDS libposlv
)

remake_pack_deb(
  COMPONENT console-tools
  DESCRIPTION "Console tools"
  DEPENDS libposlv
)

remake_pack_deb(
  COMPONENT gui-tools
  DESCRIPTION "GUI tools"
  DEPENDS libposlv libqtgui4
)

remake_pack_deb(
  COMPONENT gui-tools-dev
  DESCRIPTION "GUI tools development headers"
  DEPENDS libposlv-dev libposlv-gui-tools libqt4-dev
)

remake_pack_deb(
  COMPONENT map-tools
  DESCRIPTION "Map tools"
  DEPENDS libposlv-gui-tools libboost-system[0-9.]* libboost-filesystem[0-9.]*
    libqt4-opengl libftgl2
)

remake_pack_deb(
  COMPONENT map-tools-dev
  DESCRIPTION "Map tools development headers"
  DEPENDS libposlv-dev libposlv-map-tools libeigen2-dev libqt4-opengl-dev
)

remake_pack_deb(
  COMPONENT geo-tools
  DESCRIPTION "Geodetic tools"
  DEPENDS libposlv
)

remake_pack_deb(
  COMPONENT geo-tools-dev
  DESCRIPTION "Geodetic tools development headers"
  DEPENDS libposlv-dev libposlv-geo-tools libeigen2-dev
)

remake_pack_deb(
  COMPONENT ntrip
  DESCRIPTION "NTRIP client"
  DEPENDS libposlv libboost-program-options[0-9.]*
)

remake_pack_deb(
  COMPONENT ntrip-dev
  DESCRIPTION "NTRIP client development headers"
  DEPENDS libposlv-dev libposlv-ntrip
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  DEPENDS libposlv
)

remake_distribute_deb(
  DISTRIBUTION lucid
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen libqt4-opengl-dev libftgl-dev libboost-all-dev
    libeigen2-dev pkg-config
  PASS CMAKE_BUILD_TYPE LIBPOSLV_GIT_REVISION
)

remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen libqt4-opengl-dev libftgl-dev libboost-all-dev
    libeigen2-dev pkg-config
  PASS CMAKE_BUILD_TYPE LIBPOSLV_GIT_REVISION
)

remake_distribute_deb(
  DISTRIBUTION trusty
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen libqt4-opengl-dev libftgl-dev libboost-all-dev
    libeigen2-dev pkg-config
  PASS CMAKE_BUILD_TYPE LIBPOSLV_GIT_REVISION
)
