#include "blockImage.h"

vector<blockImage> block_image;

void init_image() {
  block_image.resize(5);

  unsigned long i = 0;
  block_image[i++].setDir("./image/default.dat");
  block_image[i++].setDir("./image/start.dat");
  block_image[i++].setDir("./image/goal.dat");
  block_image[i++].setDir("./image/default.dat"); // mv_block
  block_image[i++].setDir("./image/minus.dat"); // mv_block
  //block_image[i++].setDir("");

  for(i = 0; i < block_image.size(); i++) {
    block_image[i].readImage();
  }
}

