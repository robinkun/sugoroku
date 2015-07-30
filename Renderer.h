#pragma once
#include <iostream>
#include <ncurses.h>
#include "block.h"

using namespace std;

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

    blockImage* img = bl->image();
    move(1 + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE);
    for(unsigned long i = 0; i < img->_image.size(); i++) {
      for(unsigned long j = 0; j < img->_image.size(); j++) {
        mvaddch(i+1 + bl->y()*BLOCK_SIZE, j+1 + bl->x()*BLOCK_SIZE, img->_image[i][j]);
      }
    }
    /*
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
      case -1: // 進む
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "|1|");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
      default:
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "| |");
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "---");
        break;
    }
        mvprintw(h++ + bl->y()*BLOCK_SIZE, 1 + bl->x()*BLOCK_SIZE, "%d", img->_image.size());*/
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
