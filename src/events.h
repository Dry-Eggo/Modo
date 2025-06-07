#pragma once

#include <functional>
#include <iterator>
#include <map>
#include <string>
#include <variant>
#include <vector>

struct Event;
typedef std::function<void(Event *)> EventListener;
typedef std::pair<int, int> MouseLoc;

struct Event {
  std::variant<std::string, int, MouseLoc, void *> data;
};

struct EventManager {
  std::map<std::string, std::vector<EventListener>> listerners;
  void on(std::string eventkey, EventListener callback) {
    this->listerners[eventkey].push_back(callback);
  }
  void emit(std::string eventkey, Event *data) {
    if (this->listerners.count(eventkey) == 0) {
      return;
    }

    auto callbacks = this->listerners[eventkey];
    for (auto callback : callbacks) {
      callback(data);
    }
  }
};
