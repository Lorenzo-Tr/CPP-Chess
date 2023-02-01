#pragma once
#include <list>
#include <string>
#include "ChessBoard.hpp"
#include "E_Color.hpp"
#include "Player.hpp"

using namespace std;
class Game {
 private:
  ChessBoard chessboard_;
  array<Player*, 2> players_;
  Player actual_player_;
  list<string> historical_;

 public:
  Game(const string& fen =
           "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  inline ChessBoard GetChessBoard() const { return chessboard_; }
  inline Player GetActualPlayer() const { return actual_player_; }
  inline list<string> GetHistorical() const { return historical_; }

  void change_player(E_Color color);
  int cancel_move();
  bool check_echec(int x, int y);
  bool check_mat(int x, int y);
  bool check_pat(int x, int y);
  bool check_castle(int x, int y);
  bool do_roque(int x, int y);
};