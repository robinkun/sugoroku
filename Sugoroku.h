#pragma once
#include <string>
#include "board.h"
#include "Renderer.h"

class Sugoroku {
  board* b;
  Renderer *r;

public:

  Sugoroku(string directory) {
    b = new board();
    r = new Renderer(b);
    readFile(b, directory);
  }

  ~Sugoroku() {
    delete r;
    delete b;
  }

  int sugorokuMain() {
    while(1)
      r->render_board();
  }
};
