#include <stdio.h>
#include "board.h"

void sugoroku_main();

int main(void) {
  sugoroku_main();
  return 0;
}

void sugoroku_main() {
  board* b = new board();
  b->readFile("./test.dat");
}
