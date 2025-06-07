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
    UI::init();
    UI *main_ui = UI::default_ui();
    this->windows.push_back(main_ui);
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
  ~App() {
    delete em;
    delete keym;
    for (auto win : windows) {
      delete win;
    }
  }
};
