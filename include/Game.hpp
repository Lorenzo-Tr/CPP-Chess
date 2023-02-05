#pragma once
#include <list>
#include <string>
#include "ChessBoard.hpp"
#include "E_Color.hpp"
#include "Historical.hpp"
#include "Player.hpp"

using namespace std;
class Game {
 private:
  ChessBoard chessboard_;
  array<Player*, 2> players_;
  Player* actual_player_;

 public:
  Game(const string& fen =
           "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
  inline ChessBoard& GetChessBoard() { return chessboard_; }
  inline Player* GetActualPlayer() { return actual_player_; }

  void change_player();
  void cancel_move();
  void generateLegalMoves(E_Color ColourToMove);
  void save_move(Move* move, Piece* captured, Piece* promoted);
  bool check_echec();
  bool check_mat();
  bool check_pat();
  bool check_castle();
  void do_castle();
};