#pragma once
#include "block.h"
#include <vector>

class goalBlock : public block {
public:
  goalBlock(int type, int x, int y) : block(type, x, y) {
  }

  blockImage* image() {
    return &block_image[2];
  }
};
