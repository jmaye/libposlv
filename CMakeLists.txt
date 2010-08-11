cmake_minimum_required(VERSION 2.6)

include(ReMake)

remake_project(
  libposlv
  VERSION 0.1
  RELEASE alpha
  SUMMARY "Applanix POS LV driver"
  AUTHOR "Jerome Maye"
  CONTACT "jerome.maye@mavt.ethz.ch"
  HOME "http://aslforge.ethz.ch/projects/libposlv"
  LICENSE "GNU Lesser General Public License (LGPL)"
  PREFIX poslv-
  INSTALL /usr/
)

remake_doc(
  html
)

remake_pack_deb(
  DESCRIPTION "Main library"
)

remake_pack_deb(
  COMPONENT dev
  DESCRIPTION "Development headers"
)

remake_pack_deb(
  COMPONENT test
  DESCRIPTION "Test programs"
  libposlv
)

remake_pack_deb(
  COMPONENT doc
  DESCRIPTION "Documentation"
)
