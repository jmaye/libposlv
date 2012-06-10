remake_qt4_ui(visualization)
remake_qt4_moc(visualization)

remake_add_library(visualization LINK ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES}
  sensor)
remake_add_headers(INSTALL visualization)
