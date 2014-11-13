remake_qt4_include()
remake_find_package(Threads)
if(NOT ${CMAKE_USE_PTHREADS_INIT})
  message(FATAL_ERROR "Missing POSIX thread support!")
endif(NOT ${CMAKE_USE_PTHREADS_INIT})
remake_find_package(Boost COMPONENTS program_options system filesystem
  RESULT_VAR Boost_FOUND)
remake_find_file(eigen2/Eigen/Core PACKAGE libeigen2-dev)
#remake_find_package(eigen2 CONFIG)
remake_find_package(ftgl CONFIG)

remake_project_header(config.h.remake)

#remake_include(${Boost_INCLUDE_DIR} ${EIGEN2_INCLUDE_DIRS}
#  ${FTGL_INCLUDE_DIRS})
remake_include(${Boost_INCLUDE_DIR} ${LIBEIGEN2_DEV_PATH}/eigen2
  ${FTGL_INCLUDE_DIRS})

remake_add_directories(lib)
remake_add_directories(bin)
