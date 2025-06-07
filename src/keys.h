#pragma once

#include "events.h"
#include "ui.h"
#include <ncurses.h>
struct KeyBoardManager {
  EventManager *em;
  KeyBoardManager(EventManager *em) : em(em) {}
  void update(UI *win) {
    int ch = wgetch(win->win);
    if (ch == 'q') {
      em->emit("KeyPress:q", NULL);
    }
  }
};
