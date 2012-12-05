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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "sensor/Utils.h"

#include <cmath>

#include <sstream>

#include <boost/filesystem.hpp>

#include "com/HTTPProtocol.h"
#include "com/TCPConnectionClient.h"
#include "com/NetUtils.h"
#include "base/BinaryStreamWriter.h"
#include "base/BinaryStreamReader.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"

namespace Utils {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void WGS84ToLV03(double latitude, double longitude, double altitude,
    double& east, double& north, double& height) {
  latitude = decToSexAngle(latitude);
  longitude = decToSexAngle(longitude);
  latitude = sexAngleToSeconds(latitude);
  longitude = sexAngleToSeconds(longitude);
  double latitudeAux = (latitude - 169028.66) / 10000;
  double longitudeAux = (longitude - 26782.5) / 10000;
  east = 600072.37 + 211455.93 * longitudeAux - 10938.51 * longitudeAux *
    latitudeAux - 0.36 * longitudeAux * latitudeAux * latitudeAux
    - 44.54 * longitudeAux * longitudeAux * longitudeAux;
  north = 200147.07 + 308807.95 * latitudeAux + 3745.25 * longitudeAux *
    longitudeAux + 76.63 * latitudeAux * latitudeAux - 194.56 * longitudeAux *
    longitudeAux * latitudeAux + 119.79 * latitudeAux * latitudeAux *
    latitudeAux;
  height = altitude - 49.55 + 2.73 * longitudeAux + 6.94 * latitudeAux;
}

void LV03ToWGS84(double& latitude, double& longitude, double& altitude,
    double east, double north, double height) {
  double eastAux = (east - 600000) / 1000000;
  double northAux = (north - 200000) / 1000000;
  longitude = 2.6779094 + 4.728982 * eastAux + 0.791484 * eastAux * northAux +
    0.1306 * eastAux * northAux * northAux - 0.0436 * eastAux * eastAux *
    eastAux;
  longitude = longitude * 100 / 36;
  latitude = 16.9023892 + 3.238272 * northAux - 0.270978 * eastAux * eastAux
    - 0.002528 * northAux * northAux - 0.0447 * eastAux * eastAux * northAux
    - 0.0140 * northAux * northAux * northAux;
  latitude = latitude * 100 / 36;
  altitude = height + 49.55 - 12.60 * eastAux - 22.64 * northAux;
}

double sexToDecAngle(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = floor(dms);
  min = floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return deg + min / 60 + sec / 3600;
}

double decToSexAngle(double dec) {
  int deg = floor(dec);
  int min = floor((dec - deg) * 60);
  double sec = (((dec - deg) * 60) - min) * 60;
  return deg + (double)min/100 + (double)sec/10000;
}

double sexAngleToSeconds(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = floor(dms);
  min = floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return sec + (double)min * 60 + (double)deg * 3600;
}

double deg2rad(double deg) {
  return deg * M_PI / 180.0;
}

double rad2deg(double rad) {
  return rad * 180.0 / M_PI;
}

std::string downloadMapTile(double east, double north, double zoomLevel,
    const std::string& dir, size_t width, size_t height,
    const MapType type, const MapFormat format) {
  std::stringstream imgFileName;
  imgFileName << mapTypes[type] << "_" << (int)east << "_" << (int)north
    << "_" << zoomLevel << "_" << width << "_" << height << "."
    << mapFormats[format];
  if (boost::filesystem::exists(dir + "/" + imgFileName.str()))
    return imgFileName.str();
  std::string image;
  fetchMapTile(east, north, zoomLevel, image, width, height, type, format);
  std::string fullImgFileName;
  if (dir.empty())
    fullImgFileName = imgFileName.str();
  else
    fullImgFileName = dir + "/" + imgFileName.str();
  std::ofstream imageFile(fullImgFileName.c_str());
  if (!imageFile.is_open())
    throw IOException("MapTools::downloadMapTile(): image write failed");
  imageFile.write(image.c_str(), image.size());
  imageFile.close();
  return imgFileName.str();
}

void fetchMapTile(double east, double north, double zoomLevel,
    std::string& image, size_t width, size_t height,
    const MapType type, const MapFormat format) {
  std::stringstream uri;
  uri << "/chmap.en." << mapFormats[format] << "?x=0m&y=0m&w=" << width << "&h="
    << height << "&base=" << east << "," << north << "&layer="
    << mapTypes[type] << "&zd=" << zoomLevel<< "&n=0";
  std::string httpRequest;
  httpRequest += HTTPProtocol::writeRequestLine(HTTPProtocol::Method::GET,
    uri.str());
  httpRequest += HTTPProtocol::writeGeneralHeaderLine(
    HTTPProtocol::GeneralHeader::Connection, "close");
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::Host, serverHost);
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::UserAgent, "swissMap");
  httpRequest += "\r\n";
  TCPConnectionClient com(NetUtils::getHostIP(serverHost), serverPort);
  BinaryStreamReader<TCPConnectionClient> tcpStreamReader(com);
  BinaryStreamWriter<TCPConnectionClient> tcpStreamWriter(com);
  com.open();
  tcpStreamWriter << httpRequest;
  std::string responseStatusLine =
    HTTPProtocol::readLine(tcpStreamReader);
  std::string protocol, statusCode, reasonPhrase;
  HTTPProtocol::readResponseStatusLine(responseStatusLine, protocol,
    statusCode, reasonPhrase);
  if (statusCode != "200") {
    std::stringstream status;
    status << "status code: " + statusCode + "\nreason: " + reasonPhrase;
    throw IOException("MapTools::fetchMapTile(): " + status.str());
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
        HTTPProtocol::entityHeaders[
        HTTPProtocol::EntityHeader::ContentType]
        &&
        value.compare(0, 8, "image/" + mapFormats[format], 0, 8))
      throw IOException("MapTools::fetchMapTile(): wrong image format");
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
  image.clear();
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
  com.close();
}

}
