#pragma once
#include <string>
using namespace std;
class Player {
 private:
  bool color_;
  string name_;

 public:
  Player(string name, bool color);
  int play_shot(int x1, int y1, int x2, int y2);
  int shot(int x, int y);
};