#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "masu.h"
#include "person.h"
#include "utils.h"

using namespace std;

class board {
  masu* root;
  vector<person> persons;

public:
  board() {}
  void readLoop(masu* ptr, ifstream &ifs) {
    string str;
    int direction, type; // $B%^%9$NJ}8~$H%?%$%W(B
    int at;
    unsigned int hierarchy;

    while(getline(ifs, str)) {
      for(hierarchy = 0; str.at(hierarchy) == ' ' &&
          hierarchy < str.size(); hierarchy++);
      at = hierarchy;
      // $BJ}8~(B
      direction = str.at(at++) - '0';
      type = str.at(at++) - '0';
      ptr->setNext(new masu(type), direction);
      // $BH?BPJ}8~(B
      ptr->next(direction)->setPrev(ptr, reverse_dir(direction));
      for(int dir = 0; dir < DIR_NUM; dir++) {
        if(ptr->next(dir)) readLoop(ptr, ifs);
      }
    }
  }

  int readFile(string dir) {
    ifstream ifs(dir);

    if(ifs.fail()) return 1;

    root = new masu(-1);
    readLoop(root, ifs);

    return 0;
  }
};
