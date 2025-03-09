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

  private:
    std::string name;
    int id;
    std::string code;
    bool hasparking;
};

#endif //LOCATION_H
