#include "Piece.hpp"
#include <string>

using namespace std;

/* -------------------------------------------- */
/*                     Piece                    */
/* -------------------------------------------- */
Piece::Piece(int x, int y, bool color, ChessBoard* board)
    : x_(x), y_(y), color_(color), board_(board) {}

/* -------------------------------------------- */
/*                     King                     */
/* -------------------------------------------- */

King::King(int x, int y, bool color, ChessBoard* board) : Piece(x, y, color, board) {}
bool King::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = getX() - x;
  int diffY = getY() - y;

  if (diffX == 1 || diffX == -1 || diffY == 1 || diffY == -1)
    return true;

  return false;
}

void King::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                     Queen                    */
/* -------------------------------------------- */

Queen::Queen(int x, int y, bool color, ChessBoard* board) : Piece(x, y, color, board) {}
bool Queen::validate_move(int x, int y) {
  if (x > 8 || x < 0 || y > 7 || y < 7)
    return false;

  if (getY() == y && x < 7 && x >= 0)
    return true;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY)
    return true;

  return false;
}
void Queen::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                     Rook                     */
/* -------------------------------------------- */
Rook::Rook(int x, int y, bool color, ChessBoard* board)
    : Piece(x, y, color, board) {}
bool Rook::validate_move(int x, int y) {}
void Rook::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                    Knight                    */
/* -------------------------------------------- */
Knight::Knight(int x, int y, bool color, ChessBoard* board) : Piece(x, y, color, board) {}
bool Knight::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  if (diffX == 2 && diffY == 1 || diffX == 1 && diffY == 2)
    return true;

  return false;
}
void Knight::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

/* -------------------------------------------- */
/*                    Bishop                    */
/* -------------------------------------------- */
Bishop::Bishop(int x, int y, bool color, ChessBoard* board)
    : Piece(x, y, color, board) {}
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
Pawn::Pawn(int x, int y, bool color, bool already_move, ChessBoard* board)
    : Piece(x, y, color, board), already_move_(already_move) {}

bool Pawn::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || x < 0)
    return false;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  bool can_move;

  if (already_move_)
    if (diffY == 2 || diffY == 1)
      return true;

  if (diffY == 1)
    return true;

  if (diffY == 1 && diffX == 1)
    return true;

  return false;
}
void Pawn::move(int x, int y) {
  already_move_ == false;
  if (validate_move(x, y)) {
  }
}

void Pawn::forward() {}

void Pawn::promote() {}
