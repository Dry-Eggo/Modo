#pragma once

#include <fstream>
#include <ios>
#include <sstream>
#include <string>
#include <vector>

struct Buffer {
  std::string filename;
  std::string data;
  std::vector<std::string> lines;
  int cursorx = 0;
  int cursory = 0;
  Buffer() = default;

  // Load file contents into buffer
  void load_from_file(const char *path) {
    std::ifstream file(path, std::ios::in);
    if (!file.is_open()) {
      return;
    }

    this->filename = path;

    std::stringstream ss;
    ss << file.rdbuf();
    this->data = ss.str();

    this->lines.clear();
    std::string line;
    std::istringstream stream(this->data);
    while (std::getline(stream, line)) {
      this->lines.push_back(line);
    }

    cursorx = 0;
    cursory = 0;

    file.close();
  }

  std::string current_line() const {
    if (cursory >= 0 && cursory < (int)lines.size()) {
      return lines[cursory];
    }
    return "";
  }

  void insert_char(char c) {
    if (cursory >= (int)lines.size()) {
      lines.resize(cursory + 1);
    }

    std::string &line = lines[cursory];

    if (cursorx > (int)line.size()) {
      line.resize(cursorx, ' ');
    }

    line.insert(line.begin() + cursorx, c);
    cursorx++;
    rebuild_data();
  }

  void backspace() {
    if (cursory >= (int)lines.size()) return;

    std::string &line = lines[cursory];

    if (cursorx > 0 && cursorx <= (int)line.size()) {
      line.erase(line.begin() + cursorx - 1);
      cursorx--;
    } else if (cursorx == 0 && cursory > 0) {
      // Join with previous line
      std::string &prev = lines[cursory - 1];
      cursorx = prev.size();
      prev += line;
      lines.erase(lines.begin() + cursory);
      cursory--;
    }

    rebuild_data();
  }

  // Rebuild raw data from lines
  void rebuild_data() {
    std::stringstream ss;
    for (size_t i = 0; i < lines.size(); ++i) {
      ss << lines[i];
      if (i + 1 < lines.size()) {
        ss << "\n";
      }
    }
    this->data = ss.str();
  }

  void save_to_file(const char *path = nullptr) {
    const char *out_path = path ? path : this->filename.c_str();
    if (!out_path) return;

    std::ofstream out(out_path, std::ios::out);
    if (!out.is_open()) return;

    out << this->data;
    out.close();
  }
};