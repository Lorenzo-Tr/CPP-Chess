#pragma once
#include <E_Color.hpp>
#include <array>
#include <iostream>
#include <string>
#include "ChessBoard.hpp"

using namespace std;

class Player {
 private:
  ChessBoard& chessboard_;
  string name_;
  E_Color color_;

 public:
  Player(ChessBoard& chessboard, string name, E_Color color);
  inline E_Color getColor() { return color_; }
  inline string getName() { return name_; }

  int play_move(int x1, int y1, int x2, int y2);
  array<int, 4> read_move();
};