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

/** \file dgpsClient.cpp
    \brief This file is a testing binary for the dgps client.
  */

#include <iostream>

#include <boost/program_options.hpp>

#include "sensor/NTRIPClient.h"
#include "com/HTTPProtocol.h"
#include "com/SerialConnection.h"

#include "config.h"

namespace po = boost::program_options;

struct Options {
  std::string host;
  std::string port;
  std::string mountPoint;
  std::string userName;
  std::string password;
  std::string serialDevice;
  std::string baudRate;
  std::string dataBits;
  std::string stopBits;
  std::string parity;
  std::string flowControl;
};

bool processCommandLine(int argc, char** argv, Options& options) {
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help", "Display this information")
      ("version,v", "Display version information")
      ("host,h", po::value<std::string>(&options.host),
        "Set the host server name")
      ("port,p", po::value<std::string>(&options.port)->default_value("80"),
        "Set the host server port")
      ("mountpoint,m", po::value<std::string>(&options.mountPoint),
        "Set the mountpoint")
      ("user,u", po::value<std::string>(&options.userName), "Set the username")
      ("password", po::value<std::string>(&options.password),
        "Set the password")
      ("serialdevice,s", po::value<std::string>(&options.serialDevice),
        "Set the serial device")
      ("baudrate,b", po::value<std::string>(&options.baudRate),
        "Set the serial baudrate")
      ("databits,d", po::value<std::string>(&options.dataBits),
        "Set the serial databits")
      ("stopbits", po::value<std::string>(&options.stopBits),
        "Set the serial stopbits")
      ("parity", po::value<std::string>(&options.parity),
        "Set the serial parity")
      ("flowcontrol", po::value<std::string>(&options.flowControl),
        "Set the serial flow control");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help") || argc == 1) {
      std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
      std::cout << desc << std::endl;
      return false;
    }
    if (vm.count("version")) {
        std::cout << PROJECT_NAME << " " << PROJECT_MAJOR << "."
          << PROJECT_MINOR << "." << PROJECT_PATCH << std::endl
          << "Copyright (C) 2011 by "
          << PROJECT_CONTACT << std::endl << PROJECT_LICENSE << std::endl;
        return false;
    }
    if (!vm.count("host")) {
      std::cerr << "'host' parameter not set" << std::endl;
      return false;
    }
    if (!vm.count("mountpoint")) {
      std::cerr << "'mountpoint' parameter not set" << std::endl;
      return false;
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  Options options;
  if (!processCommandLine(argc, argv, options))
    return 1;
  NTRIPClient ntripClient(options.host, atoi(options.port.c_str()),
    options.mountPoint, options.userName, options.password);
  ntripClient.open();
  ntripClient.requestLiveStream();
  while (1)
    std::cout << HTTPProtocol::readDataChunk(ntripClient.getStreamReader());
  ntripClient.close();
  return 0;
}
