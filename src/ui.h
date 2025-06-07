#pragma once

#include <ncurses.h>
static int mw;
static int mh;
struct UI {
  WINDOW *win;
  bool focus;
  int w;
  int h;
  int x;
  int y;

  static void init() {
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    wrefresh(stdscr);
    getmaxyx(stdscr, mh, mw);
  }
  static UI *default_ui() {
    UI *def = new UI();
    def->focus = true;
    def->h = mh;
    def->w = mw;
    def->x = def->y = 0;
    def->win = newwin(def->h, def->w, def->y, def->x);
    box(def->win, 0, 0);
    return def;
  }

  void refresh() { wrefresh(this->win); }
};
