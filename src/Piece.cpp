#include "Piece.hpp"

/* -------------------------------------------- */
/*                     Piece                    */
/* -------------------------------------------- */
Piece::Piece(int x, int y, bool color) : x_(x), y_(y), color_(color) {}

/* -------------------------------------------- */
/*                     King                     */
/* -------------------------------------------- */
King::King(int x, int y, bool color) : Piece(x, y, color) {}
bool King::validate_move(int x, int y) {}
void King::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                     Queen                    */
/* -------------------------------------------- */
Queen::Queen(int x, int y, bool color) : Piece(x, y, color) {}
bool Queen::validate_move(int x, int y) {}
void Queen::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                     Rook                     */
/* -------------------------------------------- */
Rook::Rook(int x, int y, bool color) : Piece(x, y, color) {}
bool Rook::validate_move(int x, int y) {}
void Rook::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                    Knight                    */
/* -------------------------------------------- */
Knight::Knight(int x, int y, bool color) : Piece(x, y, color) {}
bool Knight::validate_move(int x, int y) {}
void Knight::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                    Bishop                    */
/* -------------------------------------------- */
Bishop::Bishop(int x, int y, bool color) : Piece(x, y, color) {}
bool Bishop::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY)
    return true;

  return false;
}
void Bishop::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                     Pawn                     */
/* -------------------------------------------- */
Pawn::Pawn(int x, int y, bool color, bool can_move)
    : Piece(x, y, color), can_move_(can_move) {}

bool Pawn::validate_move(int x, int y) {}
void Pawn::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

void Pawn::forward() {}

void Pawn::promote() {}
