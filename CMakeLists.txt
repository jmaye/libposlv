cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_set(CMAKE_CXX_FLAGS -std=c++0x CACHE FORCE INIT)

remake_project(
  libposlv
  VERSION 1.0
  RELEASE beta
  SUMMARY "A C++ based Applanix POS LV interfacing library"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "http://aslforge.ethz.ch/projects/libposlv"
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
  DEPENDS libboost-system[0-9.]* libboost-filesystem[0-9.]*
)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
  DEPENDS libposlv libeigen2-dev
)

remake_pack_deb(
  COMPONENT console-tools
  DESCRIPTION "Console tools"
  DEPENDS libposlv libboost-program-options[0-9.]*
)

remake_pack_deb(
  COMPONENT gui-tools
  DESCRIPTION "GUI tools"
  DEPENDS libposlv libqt4-opengl libftgl2
)

remake_pack_deb(
  COMPONENT gui-tools-dev
  DESCRIPTION "GUI tools development headers"
  DEPENDS libposlv-dev libqt4-opengl-dev
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
    libeigen2-dev
  PASS CMAKE_BUILD_TYPE LIBPOSLV_SUBVERSION_REVISION
)

remake_distribute_deb(
  DISTRIBUTION precise
  SECTION libs
  UPLOAD ppa:jmaye/ethz
  DEPENDS remake doxygen libqt4-opengl-dev libftgl-dev libboost-all-dev
    libeigen2-dev
  PASS CMAKE_BUILD_TYPE LIBPOSLV_SUBVERSION_REVISION
)
