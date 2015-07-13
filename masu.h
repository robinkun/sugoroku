#pragma once
#include "param.h"
#include "person.h"
#include <vector>

class masu {
  int _type;
  int _hierarchy;
  vector<masu*> _prev;
  vector<masu*> _next;
  person* root;

public:
  masu(int t) {
    _type = t;
    _prev = vector<masu*>(4, nullptr);
    _next = vector<masu*>(4, nullptr);
  }

  void setHierarchy(int h) {_hierarchy = h;}
  void setNext(masu* n, int index) {_next[index] = n;}
  void setPrev(masu* p, int index) {_prev[index] = p;}

  int hierarchy() {return _hierarchy;}
  masu* next(int index) {return _next[index];}
  masu* prev(int index) {return _prev[index];}
  int type() {return _type;}
};
