#pragma once
#include <list>
#include <string>
#include "ChessBoard.hpp"
#include "E_Color.hpp"
#include "Player.hpp"

struct Attacker {
  int x_;
  int y_;
};

using namespace std;
class Game {
 private:
  ChessBoard chessboard_;
  array<Player*, 2> players_;
  Player* actual_player_;
  list<string> historical_;

 public:
  static Attacker attacker_;
  Game(const string& fen =
           "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  inline ChessBoard& GetChessBoard() { return chessboard_; }
  inline Player* GetActualPlayer() { return actual_player_; }
  inline list<string> GetHistorical() { return historical_; }

  void change_player(E_Color color);
  int cancel_move();
  bool check_echec();
  bool check_mat();
  bool check_pat();
  bool check_castle();
  void do_castle();
};