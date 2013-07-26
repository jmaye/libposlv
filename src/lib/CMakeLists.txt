remake_include()

remake_add_directories(base)
remake_add_directories(com)
remake_add_directories(exceptions)
remake_add_directories(sensor)
remake_add_directories(types)
remake_add_directories(utils)
remake_pkg_config_generate(EXTRA_CFLAGS -std=c++0x)

remake_add_directories(data-structures COMPONENT map-tools)
remake_add_directories(map-tools COMPONENT map-tools)
remake_pkg_config_generate(COMPONENT map-tools REQUIRES libposlv-gui-tools)

remake_add_directories(geo-tools COMPONENT geo-tools)
remake_pkg_config_generate(COMPONENT geo-tools REQUIRES libposlv)

remake_add_directories(ntrip COMPONENT ntrip)
remake_pkg_config_generate(COMPONENT ntrip REQUIRES libposlv)

remake_add_directories(visualization COMPONENT gui-tools)
remake_pkg_config_generate(COMPONENT gui-tools REQUIRES libposlv)
