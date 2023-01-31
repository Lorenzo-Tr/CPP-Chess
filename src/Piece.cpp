#include "Piece.hpp"
#include <math.h>
#include <algorithm>

using namespace std;

/* -------------------------------------------- */
/*                     Piece                    */
/* -------------------------------------------- */
Piece::Piece() {}
Piece::Piece(int x, int y, E_Color color, ChessBoard* board)
    : x_(x), y_(y), color_(color), board_(board) {}

string Piece::getType() {
  return nullptr;
}

const string Piece::to_string() const {
  return ".";
}

bool Piece::operator!=(const string& s) {
  return getType() != s;
}

ostream& operator<<(ostream& os, const Piece& p) {
  os << p.to_string();
  return os;
}

/* -------------------------------------------- */
/*                     King                     */
/* -------------------------------------------- */
King::King(int x, int y, E_Color color, ChessBoard* board)
    : Piece(x, y, color, board) {}

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

string King::getType() {
  return "king";
}

const string King::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "K";
  } else {
    return "k";
  }
}

/* -------------------------------------------- */
/*                     Queen                    */
/* -------------------------------------------- */
Queen::Queen(int x, int y, E_Color color, ChessBoard* board)
    : Piece(x, y, color, board) {}

bool Queen::validate_move(int x, int y) {
  if (x > 8 || x < 0 || y > 7 || y < 7)
    return false;

  // check line
  if (getY() == y && x < 7 && x >= 0) {
    for (int i = getX(); i <= x; i++) {
      if (getBoard()[i * 8 + y] != 0)
        return false;
    }
  }
  return true;

  // check column
  if (getX() == x && y < 7 && y >= 0) {
    for (int j = getY(); j <= y; j++) {
      if (getBoard()[x * 8 + j] != 0)
        return false;
    }
  }
  return true;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);
  int dirX = getX() - x;
  int dirY = getY() - y;
  // check diagonale
  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY) {
    if ((dirX < 0 && dirY < 0) || (dirX > 0 && dirY > 0)) {
      int max_X = max(getX(), x);
      int max_Y = max(getY(), y);
      for (int i = min(getX(), x); i < max_X; i++) {
        for (int j = min(getY(), y); j < max_Y; j++) {
          if (getBoard()[i * 8 + j] != 0)
            return false;
        }
      }
    }
    if ((dirX < 0 && dirY > 0) || (dirX > 0 && dirY < 0)) {
      int max_X = max(getX(), x);
      int min_Y = min(getY(), y);
      for (int i = min(getX(), x); i < max_X; i++) {
        for (int j = max(getY(), y); j > min_Y; j--) {
          if (getBoard()[i * 8 + j] != 0)
            return false;
        }
      }
    }
    return true;
  }
  return false;
}

void Queen::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

string Queen::getType() {
  return "queen";
}

const string Queen::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "Q";
  } else {
    return "q";
  }
}

/* -------------------------------------------- */
/*                     Rook                     */
/* -------------------------------------------- */
Rook::Rook(int x, int y, E_Color color, ChessBoard* board)
    : Piece(x, y, color, board) {}

bool Rook::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  if (getY() == y && x < 7 && x >= 0)
    return true;

  return false;
}

void Rook::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

string Rook::getType() {
  return "rook";
}

const string Rook::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "R";
  } else {
    return "r";
  }
}

/* -------------------------------------------- */
/*                    Knight                    */
/* -------------------------------------------- */
Knight::Knight(int x, int y, E_Color color, ChessBoard* board)
    : Piece(x, y, color, board) {}

bool Knight::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2))
    return true;

  return false;
}

void Knight::move(int x, int y) {
  if (validate_move(x, y)) {
  }
}

string Knight::getType() {
  return "knight";
}

const string Knight::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "N";
  } else {
    return "n";
  }
}

/* -------------------------------------------- */
/*                    Bishop                    */
/* -------------------------------------------- */
Bishop::Bishop(int x, int y, E_Color color, ChessBoard* board)
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

string Bishop::getType() {
  return "bishop";
}

const string Bishop::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "B";
  } else {
    return "b";
  }
}

/* -------------------------------------------- */
/*                     Pawn                     */
/* -------------------------------------------- */
Pawn::Pawn(int x, int y, E_Color color, bool already_move, ChessBoard* board)
    : Piece(x, y, color, board), already_move_(already_move) {}

bool Pawn::validate_move(int x, int y) {
  if (x > 7 || x < 0 || y > 7 || x < 0)
    return false;

  int diffX = abs(getX() - x);
  int diffY = abs(getY() - y);

  for (int i = getY(); i <= y; i++) {
    if (getBoard()[getX() * 8 + i] != nullptr) {
      return false;
    }
  }

  if (already_move_)
    if (diffY == 2 || diffY == 1)
      return true;

  if (diffY == 1)
    return true;

  if (diffY == 1 && diffX == 1 && getBoard()[x * 8 + y] != 0)
    return true;

  return false;
}

void Pawn::move(int x, int y) {
  if (validate_move(x, y)) {
    already_move_ = true;
  }
}

string Pawn::getType() {
  return "pawn";
}

const string Pawn::to_string() const {
  if (this->getColor() == E_Color::WHITE) {
    return "P";
  } else {
    return "p";
  }
}

void Pawn::forward() {}

void Pawn::promote() {}
