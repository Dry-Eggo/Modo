
#include "app.h"
#include "ui.h"
#include <cstdio>
#include <ncurses.h>
int main(int c, char **v) {
  UI::init();
  UI *main_ui = UI::default_ui();
  App *app = new App();
  app->windows.push_back(main_ui);
  app->loop();
}
