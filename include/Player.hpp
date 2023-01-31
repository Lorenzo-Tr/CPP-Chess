#pragma once
#include <iostream>
#include <string>
#include <E_Color.hpp>
using namespace std;
class Player {
 private:
  string name_;
  E_Color color_;

 public:
  Player(string name, E_Color color);
  string getColor();
  int play_move(int x1, int y1, int x2, int y2);
  int read_move();
};