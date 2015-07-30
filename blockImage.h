#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class blockImage;
constexpr int BLOCK_SIZE = 3;
extern vector<blockImage> block_image;
void init_image();

class blockImage {
  string dir;

public:
  vector< vector<char> > _image;

public:
  blockImage() {
    _image = vector< vector<char> >(BLOCK_SIZE, vector<char>(BLOCK_SIZE));
  }

  void setDir(string directory) {
    dir = directory;
  }

  void readImage() {
    char chr;
    ifstream ifs(dir);
    ifs.get(chr);
    for(int i = 0; !ifs.eof() && i < BLOCK_SIZE*BLOCK_SIZE; ifs.get(chr)) {
      if(chr != '\n') {
        _image[i/BLOCK_SIZE][i%BLOCK_SIZE] = chr;
        i++;
      }
    }
  }
};
