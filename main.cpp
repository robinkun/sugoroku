#include <stdio.h>
#include "Sugoroku.h"

void sugoroku_main();

int main(void) {
  sugoroku_main();
  return 0;
}

void sugoroku_main() {
  Sugoroku* sugoroku = new Sugoroku("./test.dat");

  sugoroku->sugorokuMain();

  delete sugoroku;
}
