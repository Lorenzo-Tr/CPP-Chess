#pragma once

#include <array>
#include "Piece.hpp"

using namespace std;

class ChessBoard {
 private:
  array<Piece*, 64> board_;       // int[64]
  array<bool, 4> castle_rights_;  // bool[4]
  array<int, 2> en_passant_;      // int[2]

 public:
  ChessBoard();

  inline array<Piece*, 64> getBoard() { return board_; }
  inline array<bool, 4> getCastle_rights() { return castle_rights_; }
  inline array<int, 2> getEnPassant_() { return en_passant_; }

  void print();
  // Check if the move is valide
  bool check_move(int x1, int y1, int x2, int y2);
  // Play a move if is a valide move
  bool play_move(int x1, int y1, int x2, int y2);
};