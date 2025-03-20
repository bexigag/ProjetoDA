//
// Created by gonca on 09/03/2025.
//

#ifndef LOCATION_H
#define LOCATION_H

#include <string>

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

  private:
    std::string name;
    int id;
    std::string code;
    bool hasparking;
    double distW = 0;
    double distD = 0;
};

#endif //LOCATION_H
