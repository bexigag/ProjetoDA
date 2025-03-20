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
    double getDistW() const {return distW;}
    double getDistD() const {return distD;}
    void setDist(const double dist, const int d_w) {
      if (d_w == 0) {
        this->distD = dist;
        std::cout << "distD = " << this->distD << std::endl;
      }
      else {
        this->distW = dist;
        std::cout << "distW = " << this->distW << std::endl;
      }
    }

  private:
    std::string name;
    int id;
    std::string code;
    bool hasparking;
    double distW = INF;
    double distD = INF;
};

#endif //LOCATION_H
