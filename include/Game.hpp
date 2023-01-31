#pragma once
#include <list>
#include <string>
#include "ChessBoard.hpp"
#include "E_Color.hpp"

using namespace std;
class Game {
 private:
  ChessBoard chessboard_;
  E_Color actual_player_;
  list<string> historical_;

 public:
  Game(const string& fen =
           "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  inline ChessBoard GetChessBoard() const { return chessboard_; }
  inline E_Color GetActualPlayer() const { return actual_player_; }
  inline list<string> GetHistorical() const { return historical_; }

  bool change_player();
  int cancel_move();
  bool check_echec(int x, int y);
  bool check_mat(int x, int y);
  bool check_pat(int x, int y);
  bool check_castle(int x, int y);
  bool do_roque(int x, int y);
};