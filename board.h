#pragma once
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include "block_list.h"
#include "person.h"
#include "utils.h"

using namespace std;

class board {
  block* root;
  vector<person> persons;
  list<block*> blocklist;

public:
  board() {}
  ~board() {
    for(list<block*>::iterator i = blocklist.begin(); i != blocklist.end(); i++) {
      delete *i;
    }
  }

  list<block*>::iterator block_begin() {
    return blocklist.begin();
  }

  list<block*>::iterator block_end() {
    return blocklist.end();
  }

  friend int readFile(board*, string);
};





list<block*>::iterator moveIterator(list<block*>::iterator i, int num) {
  for(int j = 0; j < num; j++) i++;
  return i;
}

int readFile(board* b, string dir) {
  ifstream ifs;
  string str;
  char chr;
  int type; // マスの方向とタイプ
  int dir_tmp;
  int x, y;
  block* ptr;

  ifs.open(dir);
  if(ifs.fail()) return 1;
  b->root = new block(-1, -1, -1);
  ptr = b->root;

  for(int endflag = 0; !endflag;) {
    str.resize(0);
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(chr == '\n') puts("file error");
      str.append(1, chr);
    }
    type = stoi(str);
    str.resize(0);
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') puts("file error");
      str.append(1, chr);
    }
    x = stoi(str);
    str.resize(0);
    for(ifs.get(chr); chr != ',' && chr != '\n' && !ifs.eof(); ifs.get(chr)) {
      str.append(1, chr);
    }
    y = stoi(str);

    switch(type) {
    case 1:
      ptr = new startBlock(type, x, y);
      break;
    case 2:
      ptr = new goalBlock(type, x, y);
      break;
    case 3:
      str.resize(0);
      for(ifs.get(chr); chr != ','; ifs.get(chr)) {
        if(ifs.eof() || chr == '\n') puts("file error");
        str.append(1, chr);
      }
      ptr = new moveBlock(type, x, y, stoi(str));
      break;
    default:
      ptr = new block(type, x, y);
      break;
    }
    b->blocklist.push_back(ptr);

    // 読み飛ばし
    for(ifs.get(chr); chr != '\n'; ifs.get(chr)) {
      if(ifs.eof()) endflag = 1;
    }
    ifs.get(chr);
    if(ifs.eof()) endflag = 1;
    ifs.seekg(-1, std::ios::cur);
  }

  ifs.close();
  ifs.open(dir);
  list<block*>::iterator block_ite = b->blocklist.begin();

  for(int endflag = 0; !endflag && block_ite != b->blocklist.end(); block_ite++) {
    // 読み飛ばし
    // type
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(chr == '\n' || ifs.eof()) {
        printf("file faze2 error");
        exit(1);
      }
    }
    // x
    for(ifs.get(chr); chr != ','; ifs.get(chr)) {
      if(ifs.eof() || chr == '\n') printf("file faze2 error2");
    }
    // y
    for(ifs.get(chr); chr != ',' && chr != '\n' && !ifs.eof(); ifs.get(chr)) {
      str.append(1, chr);
    }

    if((*block_ite)->type() == 3) {
      for(ifs.get(chr); chr != ','; ifs.get(chr)) {
        if(ifs.eof() || chr == '\n') printf("file faze2 error2");
      }
    }

    for(int direction = 0; direction < DIR_NUM; direction++) {
      str.resize(0);
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
      ptr = *moveIterator(b->blocklist.begin(), stoi(str));
      str.resize(0);
      for(ifs.get(chr); chr != ',' && direction != DIR_NUM; ifs.get(chr)) {
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
      (*block_ite)->setNext(ptr, dir_tmp);
      ptr->setPrev(*block_ite, reverse_dir(dir_tmp));
    }
    ifs.get(chr);
    if(ifs.eof()) endflag = 1;
    ifs.seekg(-1, std::ios::cur);
  }

  return 0;
}

