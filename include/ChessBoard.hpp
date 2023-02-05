#pragma once

#include <array>
#include "Piece.hpp"

using namespace std;

class ChessBoard {
 private:
  array<Piece*, 64> board_;       // int[64]
  array<bool, 4> castle_rights_;  // bool[4]
  array<int, 2> en_passant_;      // int[2]
  const int DirectionOffsets[8] = {8, -8, -1, 1, 7, -7, 9, -9};
  int** NumSquaresToEdge;

 public:
  ChessBoard();
  ~ChessBoard();

  inline array<Piece*, 64>& getBoard() { return board_; }
  inline array<bool, 4>& getCastle_rights() { return castle_rights_; }
  inline array<int, 2>& getEnPassant() { return en_passant_; }

  inline void setBoard(array<Piece*, 64> board) { board_ = board; }
  inline void setCastleRights(array<bool, 4> castle_rights) {
    castle_rights_ = castle_rights;
  }
  inline void setEnPassant(array<int, 2> en_passant) {
    en_passant_ = en_passant;
  }

  void PrecomputedMoveDate();
  void print();
  void print_playable_move(int x, int y);
  // Check if the move is valide
  bool check_move(int x1, int y1, int x2, int y2);
  // Play a move if is a valide move
  bool play_move(int x1, int y1, int x2, int y2);
  void generateMoves(E_Color ColourToMove);
  void generateSlidingMoves(int start, Piece* piece);
  void generateKnightMoves(int start, Piece* piece);
  void generatePawnMoves(int start, Piece* piece);
  void generateKingMoves(int start, Piece* piece);
};