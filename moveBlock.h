#pragma once
#include "block.h"
#include <vector>

class moveBlock : public block {
  int mv_num;

public:
  moveBlock(int type, int x, int y, int movenum) : block(type, x, y) {
    mv_num = movenum;
  }

  blockImage* image() {
    if(mv_num >= 0) {
      block_image[3]._image[1][1] = '0' + mv_num;
      return &block_image[3];
    } else {
      block_image[4]._image[1][1] = '0' + mv_num*-1;
      return &block_image[4];
    }
    return &block_image[3];
  }
};
