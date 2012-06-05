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
  libposlv
  libboost-dev
)

remake_pack_deb(
  COMPONENT console-tools
  DESCRIPTION "Console tools"
  libposlv
  libboost-program-options-dev
)

remake_pack_deb(
  COMPONENT gui-tools
  DESCRIPTION "GUI tools"
  libposlv
  libqt4-gui
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
  libposlv
)
