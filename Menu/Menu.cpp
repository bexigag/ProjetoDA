//
// Created by bexigag on 05/03/2025.
//

#include <iostream>

using namespace std;

int main(){
  cout << "Menu" << endl;
  cout << "1 Parse Input Data" << endl;
  cout << "2 Route Planning Functionalities (driving only)" << endl;
  cout << "3 Environmentally-Friendly Route Planning (driving and walking)" << endl;
  cout << "4 Exit" << endl;

  bool flag = true;
  while(flag) {
    int option;
    cin >> option;
    switch(option) {
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        flag = false;
        break;
      default:
        cout << "Seu burro, só podes escolher até 4" << endl;
    }
  }

  return 0;
}