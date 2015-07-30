#pragma once
#include <iostream>
#include <ncurses.h>
#include "block.h"

using namespace std;
constexpr int BLOCK_SIZE = 3;

class Renderer {
  board *b;
  WINDOW* w;

public:
  Renderer(board* b) {
    this->b = b;
    this->w = initscr();
    noecho(); // 入力した文字を表示しない
    curs_set(0); // カーソルを表示しない
  }

  ~Renderer() {
    endwin();
  }

  void render_block(block* bl) {
    int h = 1; // 枠の分1増やしとく

    move(1 + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE);
    switch(bl->type()) {
      case 0: // スタート
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "|S|");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
      case 1: // ゴール
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "|G|");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
      case 2: // 進む
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "|+|");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
      default:
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "| |");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
    }
  }

  void render_board() {
    int width, height;

    getmaxyx(this->w, height, width);
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        move(i, j);
        if(i == 0 || i == height-1) {
          printw("-");
        } else if(j == 0 || j == width-1) {
          printw("|");
        } else {
          printw(" ");
        }
      }
    }

    list<block*>::iterator i = b->block_begin();
    for(; i != b->block_end(); i++) {
      render_block(*i);
    }
    refresh();
  }
};
