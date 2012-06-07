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

/** \file swissMapFetcher.cpp
    \brief This file is a testing binary for fetching Swiss maps.
  */

#include <iostream>
#include <fstream>
#include <string>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "com/TCPConnectionClient.h"
#include "com/HTTPProtocol.h"
#include "com/NetUtils.h"
#include "data-structures/Grid.h"
#include "data-structures/MapGrid.h"
#include "base/BinaryStreamWriter.h"
#include "base/BinaryStreamReader.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"
#include "exceptions/BadArgumentException.h"

#include "config.h"

namespace po = boost::program_options;

struct Options {
  std::string host;
  size_t port;
  double zoom;
  size_t width;
  size_t height;
  double minEast;
  double maxEast;
  double minNorth;
  double maxNorth;
  std::string format;
  std::string dir;
  bool aerial;
  bool info;
};

bool processCommandLine(int argc, char** argv, Options& options) {
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help", "Display this information")
      ("version", "Display version information")
      ("host,h", po::value<std::string>(&options.host)
        ->default_value("map.search.ch"), "Set the host server name")
      ("port,p", po::value<size_t>(&options.port)->default_value(80),
        "Set the host server port")
      ("zoom,z", po::value<double>(&options.zoom)->default_value(512),
        "Set the host server port")
      ("width", po::value<size_t>(&options.width)->default_value(256),
        "Set the pixel width")
      ("height", po::value<size_t>(&options.height)->default_value(256),
        "Set the pixel heigth")
      ("min-east", po::value<double>(&options.minEast)->default_value(468604),
        "Set the minimum east coordinate")
      ("max-east", po::value<double>(&options.maxEast)->default_value(853898),
        "Set the maximum east coordinate")
      ("min-north", po::value<double>(&options.minNorth)->default_value(60945),
        "Set the minimum north coordinate")
      ("max-north", po::value<double>(&options.maxNorth)->default_value(317923),
        "Set the maximum north coordinate")
      ("format", po::value<std::string>(&options.format)->default_value("png"),
        "Set the image format")
      ("dir", po::value<std::string>(&options.dir)->default_value(""),
        "Set the output directory")
      ("aerial", "Set aerial images")
      ("info", "Set info map");
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
          << "Copyright (C) 2012 by "
          << PROJECT_CONTACT << std::endl << PROJECT_LICENSE << std::endl;
        return false;
    }
    if (vm.count("aerial"))
      options.aerial = true;
    else
      options.aerial = false;
    if (vm.count("info"))
      options.info = true;
    else
      options.info = false;
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
  try {
    MapGrid mapTiles(MapGrid::Coordinate(options.minEast, options.minNorth),
      MapGrid::Coordinate(options.maxEast, options.maxNorth),
      MapGrid::Coordinate(options.zoom * options.width,
      options.zoom * options.height));
    std::string mapType;
    if (options.aerial)
      mapType = "bg";
    else
      mapType = "sym";
    if (options.info)
      mapType = "fg";
    std::stringstream gridFileName;
    gridFileName << "grid_" << mapType << "_" << options.minEast << "_"
      << options.minNorth << "_" << options.maxEast << "_" << options.maxNorth
      << "_" << (int)(options.zoom * options.width) << "_"
      << (int)(options.zoom * options.height) << ".bin";
    if (boost::filesystem::exists(options.dir + gridFileName.str())) {
      std::ifstream gridFile(options.dir + gridFileName.str());
      std::cout << "skipping " << gridFileName.str() << std::endl;
      mapTiles.readBinary(gridFile);
      std::cout << "content: " << std::endl << mapTiles << std::endl;
      return 0;
    }
    for (MapGrid::Index i = MapGrid::Index::Zero();
        i != mapTiles.getNumCells(); mapTiles.incrementIndex(i)) {
      std::stringstream imgFileName;
      imgFileName << mapType << "_"
        << (int)mapTiles.getCoordinates(i)(0) << "_"
        << (int)mapTiles.getCoordinates(i)(1) << "_" << options.zoom << "."
        << options.format;
      if (boost::filesystem::exists(options.dir + imgFileName.str())) {
        std::cout << "skipping " << imgFileName.str() << std::endl;
        continue;
      }
      mapTiles[i] = imgFileName.str();
      std::stringstream uri;
      uri << "/chmap.en." << options.format << "?x=0m&y=0m&w="
        << options.width << "&h=" << options.height << "&base="
        << mapTiles.getCoordinates(i)(0) << "," << mapTiles.getCoordinates(i)(1)
        << "&layer=" << mapType << "&zd=" << options.zoom<< "&n=0";
      std::string httpRequest;
      httpRequest += HTTPProtocol::writeRequestLine(HTTPProtocol::Method::GET,
        uri.str());
      httpRequest += HTTPProtocol::writeGeneralHeaderLine(
        HTTPProtocol::GeneralHeader::Connection, "close");
      httpRequest += HTTPProtocol::writeRequestHeaderLine(
        HTTPProtocol::RequestHeader::Host, options.host);
      httpRequest += HTTPProtocol::writeRequestHeaderLine(
        HTTPProtocol::RequestHeader::UserAgent, "swissMap");
      httpRequest += "\r\n";
      TCPConnectionClient com(NetUtils::getHostIP(options.host), options.port);
      BinaryStreamReader<TCPConnectionClient> tcpStreamReader(com);
      BinaryStreamWriter<TCPConnectionClient> tcpStreamWriter(com);
      com.open();
      tcpStreamWriter << httpRequest;
      std::string responseStatusLine = HTTPProtocol::readLine(tcpStreamReader);
      std::string protocol, statusCode, reasonPhrase;
      HTTPProtocol::readResponseStatusLine(responseStatusLine, protocol,
        statusCode, reasonPhrase);
      if (statusCode != "200") {
        std::cerr << "status code: " + statusCode + "\nreason: " + reasonPhrase
          << std::endl;
        return 1;
      }
      bool chunked = false;
      size_t bytesToRead = 0;
      while (1) {
        std::string responseHeaderLine =
          HTTPProtocol::readLine(tcpStreamReader);
        if (responseHeaderLine == "\r\n")
          break;
        std::string header;
        std::string value;
        HTTPProtocol::readHeaderLine(responseHeaderLine, header, value);
        if (header ==
            HTTPProtocol::entityHeaders[HTTPProtocol::EntityHeader::ContentType]
            &&
            value.compare(0, 8, "image/" + options.format, 0, 8)) {
          std::cerr << "wrong image format returned" << std::endl;
          return 1;
        }
        if (header ==
            HTTPProtocol::generalHeaders[
            HTTPProtocol::GeneralHeader::TransferEncoding] &&
            !value.compare(0, 6, "chunked", 0, 6))
          chunked = true;
        if (header ==
            HTTPProtocol::entityHeaders[
            HTTPProtocol::EntityHeader::ContentLength])
          bytesToRead = atoi(value.c_str());
      }
      std::string image;
      if (chunked)
        while (1) {
          std::string chunk = HTTPProtocol::readDataChunk(tcpStreamReader);
          if (chunk.empty())
            break;
          image.append(chunk);
        }
      else {
        char buffer[bytesToRead];
        tcpStreamReader.read(buffer, bytesToRead);
        image.assign(buffer, bytesToRead);
      }
      std::ofstream imageFile(options.dir + imgFileName.str());
      imageFile.write(image.c_str(), image.size());
      imageFile.close();
      std::cout << imgFileName.str() << std::endl;
      com.close();
    }
    std::ofstream gridFile(options.dir + gridFileName.str());
    mapTiles.writeBinary(gridFile);
    gridFile.close();
  }
  catch (IOException& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (SystemException& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (BadArgumentException<MapGrid::Coordinate>& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
