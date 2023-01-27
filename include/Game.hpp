#pragma once
#include <list>
#include <string>
#include "ChessBoard.hpp"

using namespace std;
class Game {
 private:
  ChessBoard chessboard_;
  bool actual_player_;
  list<string> historical_shots_;

 public:
  Game(ChessBoard board, bool player, list<string> historical);
  bool change_player();
  int cancel_shot();
  bool check_echec(int x, int y);
  bool check_mat(int x, int y);
  bool check_pat(int x, int y);
  bool check_roque(int x, int y);
  bool do_roque(int x, int y);
};