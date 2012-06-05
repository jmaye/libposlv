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

/** \file rtkClient.cpp
    \brief This file is a testing binary for the rtk client.
  */

#include <iostream>

#include <boost/program_options.hpp>

#include "sensor/NTRIPClient.h"
#include "com/HTTPProtocol.h"
#include "com/SerialConnection.h"

#include "config.h"

namespace po = boost::program_options;

bool processCommandLine(int argc, char** argv, std::string& host, std::string&
    port, std::string& streamURI, std::string& username, std::string&
    password) {
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help", "Display this information")
      ("version,v", "Display version information")
      ("host,h", po::value<std::string>(&host), "Set the host server name")
      ("port,p", po::value<std::string>(&port)->default_value("80"),
        "Set the host server port")
      ("stream,s", po::value<std::string>(&streamURI), "Set the stream URI")
      ("user,u", po::value<std::string>(&username), "Set the username")
      ("passwd", po::value<std::string>(&password), "Set the password");
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
    if (!vm.count("stream")) {
      std::cerr << "'stream' parameter not set" << std::endl;
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
  std::string host, port, streamURI, username, password;
  if (!processCommandLine(argc, argv, host, port, streamURI, username,
      password))
    return 1;
  NTRIPClient ntripClient(host, atoi(port.c_str()), streamURI, username,
    password);
  ntripClient.open();
  ntripClient.requestLiveStream();
  while (1)
    std::cout << HTTPProtocol::readDataChunk(ntripClient.getStreamReader());
  ntripClient.close();
  return 0;
}
