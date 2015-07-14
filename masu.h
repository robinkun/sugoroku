#pragma once
#include "param.h"
#include "person.h"
#include <vector>

class masu {
  int _type;
  int _hierarchy;
  int _x, _y;
  vector<masu*> _prev;
  vector<masu*> _next;
  person* root;

public:
  masu(int t, int x, int y) {
    _type = t;
    _prev = vector<masu*>(4, nullptr);
    _next = vector<masu*>(4, nullptr);
    _x = x;
    _y = y;
  }

  void setHierarchy(int h) {_hierarchy = h;}
  void setNext(masu* n, int index) {_next[index] = n;}
  void setPrev(masu* p, int index) {_prev[index] = p;}
  void setX(int x) {_x = x;}
  void setY(int y) {_y = y;}

  int hierarchy() {return _hierarchy;}
  int type() {return _type;}
  int x() {return _x;}
  int y() {return _y;}
  masu* next(int index) {return _next[index];}
  masu* prev(int index) {return _prev[index];}
};

