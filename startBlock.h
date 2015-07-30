#pragma once
#include "block.h"
#include <vector>

class startBlock : public block {
public:
  startBlock(int type, int x, int y) : block(type, x, y) {
  }

  blockImage* image() {
    return &block_image[1];
  }
};
