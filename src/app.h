#pragma once

#include "events.h"
#include "keys.h"
#include "ui.h"
#include <ncurses.h>
#include <vector>
struct App {
  std::vector<UI *> windows;
  EventManager *em;
  KeyBoardManager *keym;
  bool running = true;
  App() {
    this->em = new EventManager();
    this->keym = new KeyBoardManager(em);
  }
  void loop() {
        this->em->on("KeyPress:q", [&](Event *d) {
          this->running = false;
          endwin();
        });
    while (this->running) {
      for (auto win : this->windows) {
        if (win->focus) {
          win->refresh();
          this->keym->update(win);
        }
      }
    }
  }
};
