//
// Created by gonca on 09/03/2025.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <stack>
#include <string>
#include "../data_structures/Graph.h"

class Location {
  public:
    Location(std::string name, int id, std::string code, bool hasparking): name(name), id(id), code(code), hasparking(hasparking) {}
    bool operator == (const Location &other) const {
      return this->id == other.id || this->code == other.code;
    }
    std::string getName() const {return name;}
    int getId() const {return id;}
    std::string getCode() const {return code;}
    bool getHasParking() const {return hasparking;}

    double getDistW() {return distW;}
    double getDistD() {return distD;}

    void setDist(double dist, int d_w) {
      if (d_w == 0) {this->distD = dist;}
      else {this->distW = dist;}
    }

    void setPath(Edge<Location> *path, int d_w) {
      if (d_w == 0) {this->pathD = path;}
      else if (d_w == 1) this->pathW = path;
      else {
        this->pathD = path;
        this->pathW = path;
      }
    }

    Edge<Location> *getPathD() const {
      return pathD;
    }
    Edge<Location> *getPathW() const {
      return pathW;
    }

  private:
    std::string name;
    int id;
    std::string code;
    bool hasparking;
    double distW = 0;
    double distD = 0;
    Edge<Location> *pathD = nullptr;
    Edge<Location> *pathW = nullptr;
};

#endif //LOCATION_H
