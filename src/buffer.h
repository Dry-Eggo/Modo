#pragma once

#include <fstream>
#include <ios>
#include <string>
struct Buffer {
  std::string data;
  int cursorx;
  int cursory;

  Buffer() {}
  void load_from_file(const char *path) {
    std::fstream file = std::fstream(path, std::ios::in);
  }
};
