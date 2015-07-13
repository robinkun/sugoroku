#pragma once
#include <string>

using namespace std;

class person {
  int _num;
  string _name;

public:
  void setNum(int n) {_num = n;}
  void setName(string n) {_name = n;}

  int num() {return _num;}
  string name() {return _name;}
};
