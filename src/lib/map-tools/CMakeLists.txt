remake_qt4_ui(map-tools)
remake_qt4_moc(map-tools)

remake_add_library(map-tools LINK geo-tools visualization ${QT_QTOPENGL_LIBRARY}
  ${FTGL_LIBRARY} ${Boost_LIBRARIES})
remake_add_headers(INSTALL map-tools)
