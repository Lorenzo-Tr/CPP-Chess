#pragma once
#include "E_Color.hpp"
#include "Piece.hpp"

class Historical {
 private:
  Move* move_;
  Piece* captured_piece_;
  Piece* promoted_piece_;

 public:
  Historical(Move* m, Piece* c, Piece* p);

  inline Move* getMove() { return move_; }
  inline Piece* getCapturedPiece() { return captured_piece_; }
  inline Piece* getPromotedPiece() { return promoted_piece_; }
};