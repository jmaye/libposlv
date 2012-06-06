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

/** \file ntripClient.cpp
    \brief This file is a testing binary for an NTRIP client.
  */

#include <iostream>
#include <fstream>

#include <boost/program_options.hpp>

#include "sensor/NTRIPClient.h"
#include "com/HTTPProtocol.h"
#include "com/SerialConnection.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"

#include "config.h"

namespace po = boost::program_options;

struct Options {
  std::string host;
  size_t port;
  std::string mountPoint;
  std::string userName;
  std::string password;
  std::string serialDevice;
  size_t baudRate;
  size_t dataBits;
  size_t stopBits;
  std::string parity;
  std::string flowControl;
  std::string ntripVersion;
  std::string inFile;
  std::string outFile;
};

bool processCommandLine(int argc, char** argv, Options& options) {
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help", "Display this information")
      ("version", "Display version information")
      ("host,h", po::value<std::string>(&options.host),
        "Set the host server name")
      ("port,p", po::value<size_t>(&options.port)->default_value(80),
        "Set the host server port")
      ("mountpoint,m", po::value<std::string>(&options.mountPoint),
        "Set the mountpoint")
      ("user,u", po::value<std::string>(&options.userName), "Set the username")
      ("password,k", po::value<std::string>(&options.password),
        "Set the password")
      ("serialdevice,s", po::value<std::string>(&options.serialDevice),
        "Set the serial device")
      ("baudrate", po::value<size_t>(&options.baudRate)->default_value(19200),
        "Set the serial baudrate")
      ("databits", po::value<size_t>(&options.dataBits)->default_value(8),
        "Set the serial databits")
      ("stopbits", po::value<size_t>(&options.stopBits)->default_value(1),
        "Set the serial stopbits")
      ("parity", po::value<std::string>(&options.parity)->default_value("none"),
        "Set the serial parity")
      ("flowcontrol",
        po::value<std::string>(&options.flowControl)->default_value("no"),
        "Set the serial flow control")
      ("ntrip-version",
        po::value<std::string>(&options.ntripVersion)->default_value("2.0"),
        "Set the NTRIP protocol version")
      ("infile",
        po::value<std::string>(&options.inFile),
        "Set the NMEA input file")
      ("outfile",
        po::value<std::string>(&options.outFile),
        "Set the RTCM/CMR output file");
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
  if (options.mountPoint.empty()) {
    std::cout << "Fetching source table: " << std::endl << std::endl;
    try {
      NTRIPClient ntripClient(options.host, options.port, options.mountPoint,
        options.userName, options.password, options.ntripVersion);
      ntripClient.open();
      std::cout << ntripClient.requestSourceTable() << std::endl;
      ntripClient.close();
    }
    catch (IOException& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
    catch (SystemException& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  }
  else {
    std::cout << "Fetching live stream: " << std::endl << std::endl;
    try {
      NTRIPClient ntripClient(options.host, options.port, options.mountPoint,
        options.userName, options.password, options.ntripVersion);
      ntripClient.open();
      ntripClient.requestLiveStream();
      while (1) {
        std::string chunk;
        if (options.ntripVersion == "2.0")
          chunk = HTTPProtocol::readDataChunk(ntripClient.getStreamReader());
        else {
          uint8_t byte;
          ntripClient.getStreamReader() >> byte;
          chunk.push_back(byte);
        }
        std::cout.flush();
        std::cout << ".";
        std::ofstream outFile(options.outFile, std::ios::app);
        if (outFile.good())
          outFile.write(chunk.c_str(), chunk.size());
        outFile.close();
      }
      ntripClient.close();
    }
    catch (IOException& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
    catch (SystemException& e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  }
  return 0;
}
