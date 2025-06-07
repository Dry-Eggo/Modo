#pragma once

#include <functional>
#include <map>
#include <string>
#include <vector>

struct Event;
typedef std::function<void(Event *)> EventListener;
typedef std::pair<int, int> MouseLoc;

struct Event {
  union {
    std::string string_data;
    int int_data;
    MouseLoc mouse_location;
    void *wildcard;
  };
};

struct EventManager {
  std::map<std::string, std::vector<EventListener>> listerners;
  void on(std::string eventkey, EventListener callback) {
    this->listerners[eventkey].push_back(callback);
  }
  void emit(std::string eventkey, Event *data) {
    if (this->listerners.count(eventkey) == 0) {
      this->listerners[eventkey] = {};
      return;
    }

    auto callbacks = this->listerners[eventkey];
    for (auto callback : callbacks) {
      callback(data);
    }
  }
};
