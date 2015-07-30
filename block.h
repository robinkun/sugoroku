#pragma once
#include "param.h"
#include "person.h"
#include <vector>

class block {
  int _type;
  int _hierarchy;
  int _x, _y;
  vector<block*> _prev;
  vector<block*> _next;
  person* root;

public:
  block(int t, int x, int y) {
    _type = t;
    _prev = vector<block*>(4, nullptr);
    _next = vector<block*>(4, nullptr);
    _x = x;
    _y = y;
  }

  void setHierarchy(int h) {_hierarchy = h;}
  void setNext(block* n, int index) {_next[index] = n;}
  void setPrev(block* p, int index) {_prev[index] = p;}
  void setX(int x) {_x = x;}
  void setY(int y) {_y = y;}

  int hierarchy() {return _hierarchy;}
  int type() {return _type;}
  int x() {return _x;}
  int y() {return _y;}
  block* next(int index) {return _next[index];}
  block* prev(int index) {return _prev[index];}
};

