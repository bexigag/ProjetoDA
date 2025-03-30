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
   */
    Location(std::string name, int id, std::string code, bool hasparking): name(name), id(id), code(code), hasparking(hasparking) {}

  /**
* @brief Location comparator with id, used for running algorithms (the source and destination are id)
* @return true if the id is the same of the location´s id (bool)
*/
    bool operator == (const int id) const {
      return this->id == id;
    }

  /**
 * @brief Location comparator with code, used for reading distances
 * @return true if the code is the same of the location´s code (bool)
 */
    bool operator == (const std::string& code) const {
      return this->code == code;
    }

  /**
   * @brief getter of the name parameter
   * @return location´s name (string)
   */
    std::string getName() const {return name;}

  /**
  * @brief getter of the id parameter
  * @return location´s id (int)
  */
    int getId() const {return id;}

  /**
  * @brief getter of the code parameter
  * @return location´s code (string)
  */
    std::string getCode() const {return code;}

  /**
  * @brief getter of the hasParking parameter
  * @return location´s hasparking (true or false)
  */
    bool getHasParking() const {return hasparking;}

  /**
  * @brief getter of the distW (walking distance);
  * @return location´s distance walking (double)
  */
    double getDistW() {return distW;}

  /**
  * @brief getter of the distD (driving distance);
  * @return location´s distance driving (double)
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
* @return location´s path driving (Edge<Location>)
*/
    Edge<Location> *getPathD() const {
      return pathD;
    }

  /**
* @brief getter of the walking path
* @return location´s path walking (Edge<Location>)
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
