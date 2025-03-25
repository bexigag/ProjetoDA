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
  /**
   * @brief Constructor of the class Location
   *
   * @param name string with the name of the location
   * @param id integer with the id of the location
   * @param code string with the code of the location
   * @param hasparking boolean that indicates if the location has or doesn't have parking
   * @return Location
   */
    Location(std::string name, int id, std::string code, bool hasparking): name(name), id(id), code(code), hasparking(hasparking) {}
    bool operator == (const Location &other) const {
      return this->id == other.id || this->code == other.code;
    }

  /**
   * @brief getter of the name parameter
   * @return string
   */
    std::string getName() const {return name;}

  /**
  * @brief getter of the Id parameter
  * @return integer
  */
    int getId() const {return id;}

  /**
  * @brief getter of the code parameter
  * @return string
  */
    std::string getCode() const {return code;}

  /**
  * @brief getter of the hasParking parameter
  * @return string
  */
    bool getHasParking() const {return hasparking;}

  /**
  * @brief getter of the distw (walking distance);
  * @return double
  */
    double getDistW() {return distW;}

  /**
  * @brief getter of the distD (driving distance);
  * @return double
  */
    double getDistD() {return distD;}


  /**
   * @brief setter of the disD or distW parameters
   *
   * @param dist double
   * @param d_w integer that indicates which type of
   * distance you intend to modify if d_w==0 the distD
   * (driving distance) parameter will be modified else
   * the modified distance will be the distW (walking distance)
   * parameter
   * @return void
   */
    void setDist(double dist, int d_w) {
      if (d_w == 0) {this->distD = dist;}
      else {this->distW = dist;}
    }

  /**
 * @brief setter of the pathD or pathW parameters
 *
 * @param path Edge<Location>
 * @param d_w integer that indicates which type of
 * distance you intend to modify if d_w==0 the pathD
 * (driving path) parameter will be modified else if
 * d_w==1 the modified path will be the pathW (walking
 * path) else both paths will be updated
 * @return void
 */
  void setPath(Edge<Location> *path, int d_w) {
      if (d_w == 0) {this->pathD = path;}
      else if (d_w == 1) this->pathW = path;
      else {
        this->pathD = path;
        this->pathW = path;
      }
    }

  /**
* @brief getter of the driving path
* @return Edge<Location>
*/
    Edge<Location> *getPathD() const {
      return pathD;
    }

  /**
* @brief getter of the walking path
* @return Edge<Location>
*/
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
