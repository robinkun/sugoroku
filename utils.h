#pragma once
#include "param.h"
#include <stdio.h>

int reverse_dir(int dir) {
  dir = (DIR_NUM/2 + dir) % DIR_NUM;
  return dir;
}
