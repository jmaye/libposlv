remake_qt4_ui(visualization)
remake_qt4_moc(visualization)

remake_add_library(visualization LINK sensor ${QT_QTCORE_LIBRARY}
  ${QT_QTGUI_LIBRARY})
remake_add_headers(INSTALL visualization)
