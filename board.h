#pragma once
#include <stdio.h>
#include <vector>
#include <list>
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
  friend int readFile(board*, string);
};

int readFile(board* b, string dir) {
  ifstream ifs(dir);
  string str;
  char chr;
  int type; // マスの方向とタイプ
  int dir_tmp;
  int x, y;
  masu* ptr;
  masu* current_ptr;
  list<masu*> masulist;

  if(ifs.fail()) return 1;
  b->root = new masu(-1, -1, -1);
  ptr = b->root;

  for(int endflag = 0; !endflag;) {
    str.resize(0);
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') exit(1);
      str.append(1, chr);
    }
    type = stoi(str);
    str.resize(0);
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') exit(1);
      str.append(1, chr);
    }
    x = stoi(str);
    str.resize(0);
    for(ifs.get(chr); chr != ',' && chr != '\n' && !ifs.eof(); ifs.get(chr)) {
      str.append(1, chr);
    }
    y = stoi(str);

    ptr = new masu(type, x, y);
    masulist.push_back(ptr);

    // 読み飛ばし
    for(ifs.get(chr); chr != '\n'; ifs.get(chr)) {
      if(ifs.eof()) endflag = 1;
    }
  }

  ifs.seekg(0);
  list<masu*>::iterator masu_ite = masulist.begin();

  for(int endflag = 0; !endflag; masu_ite++) {
    // 読み飛ばし
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') exit(1);
    }
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') exit(1);
    }
    for(ifs.get(chr); chr != ',' && chr != '\n' && !ifs.eof(); ifs.get(chr)) {
      str.append(1, chr);
    }

    for(int direction = 0; direction < DIR_NUM; direction++) {
      for(ifs.get(chr); chr != ','; ifs.get(chr)) {
        if(chr == '\n') {
          direction = DIR_NUM;
          break;
        }
        if(ifs.eof()) {
          endflag = 1;
          direction = DIR_NUM;
          break;
        }
        str.append(1, chr);
      }
      ptr = masulist[stoi(str)];
      for(ifs.get(chr); chr != ','; ifs.get(chr)) {
        if(chr == '\n') {
          direction = DIR_NUM;
          break;
        }
        if(ifs.eof()) {
          endflag = 1;
          direction = DIR_NUM;
          break;
        }
        str.append(1, chr);
      }
      dir_tmp = stoi(str);
      (*masu_ite)->setNext(ptr, dir_tmp);
      ptr->setPrev(*masu_ite, reverse_dir(dir_tmp));
    }

    for(ifs.get(chr); chr != '\n'; ifs.get(chr)) {
      if(ifs.eof()) endflag = 1;
    }
    /*ptr->setNext(new masu(type), direction);
    // 反対方向
    ptr->next(direction)->setPrev(ptr, reverse_dir(direction));
    for(int dir = 0; dir < DIR_NUM; dir++) {
    if(ptr->next(dir)) readLoop(ptr, ifs);
    }*/
  }
  return 0;
}

