#include "Piece.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>

using namespace std;

bool checkDiagonals(int x_,
                    int y_,
                    int x,
                    int y,
                    const array<Piece*, 64>& board) {
  int dirX = x_ - x;
  int dirY = y_ - y;
  if ((dirX < 0 && dirY < 0) || (dirX > 0 && dirY > 0)) {
    int max_X = max(x_, x);
    int max_Y = max(y_, y);
    for (int i = min(x_, x); i < max_X; i++) {
      for (int j = min(y_, y); j < max_Y; j++) {
        if (board[i * 8 + j] != nullptr)
          return false;
      }
    }
  }
  if ((dirX < 0 && dirY > 0) || (dirX > 0 && dirY < 0)) {
    int max_X = max(x_, x);
    int min_Y = min(y_, y);
    for (int i = min(x_, x); i < max_X; i++) {
      for (int j = max(y_, y); j > min_Y; j--) {
        if (board[i * 8 + j] != nullptr)
          return false;
      }
    }
  }
  return true;
}

bool checkLine(int x_, int x, int y, const array<Piece*, 64>& board) {
  for (int i = x_; i <= x; i++) {
    if (board[i * 8 + y] != 0) {
      return false;
    }
  }
  return true;
}

bool checkColumn(int y_, int x, int y, const array<Piece*, 64>& board) {
  for (int j = y_; j <= y; j++) {
    if (board[x * 8 + j] != 0) {
      return false;
    }
  }
  return true;
}

bool checkKnight(int diffX, int diffY) {
  if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2))
    return true;

  return false;
}

/* -------------------------------------------- */
/*                     Piece                    */
/* -------------------------------------------- */
Piece::Piece(int x, int y, E_Color color) : x_(x), y_(y), color_(color) {}

string Piece::getType() {
  return nullptr;
}

const string Piece::toString() const {
  return ".";
}

bool Piece::operator!=(const string& s) {
  return getType() != s;
}

ostream& operator<<(ostream& os, const Piece& p) {
  os << p.toString();
  return os;
}

/* -------------------------------------------- */
/*                     King                     */
/* -------------------------------------------- */
King::King(int x, int y, E_Color color) : Piece(x, y, color) {}

bool King::validate_move(int x, int y, const array<Piece*, 64>& board) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  bool diagonals = !checkDiagonals(x_, y_, x, y, board);
  bool line = !checkLine(x_, x, y, board);
  bool column = !checkColumn(y_, x, y, board);
  bool knight = !checkKnight(diffX, diffY);

  if (diffX == 1 || diffY == 1) {
    if (diagonals && line && column && knight) {
      return true;
    }
  }

  return false;
}

bool King::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string King::getType() {
  return "king";
}

const string King::toString() const {
  if (color_ == E_Color::WHITE) {
    return "K";
  } else {
    return "k";
  }
}

/* -------------------------------------------- */
/*                     Queen                    */
/* -------------------------------------------- */
Queen::Queen(int x, int y, E_Color color) : Piece(x, y, color) {}

bool Queen::validate_move(int x, int y, const array<Piece*, 64>& board) {
  if (x > 8 || x < 0 || y > 7 || y < 7)
    return false;

  // check line
  if (y_ == y && x < 7 && x >= 0) {
    return checkLine(x_, x, y, board);
  }

  // check column
  if (x_ == x && y < 7 && y >= 0) {
    return checkColumn(y_, x, y, board);
  }

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  // check diagonale
  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY) {
    return checkDiagonals(x_, y_, x, y, board);
  }

  return false;
}

bool Queen::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string Queen::getType() {
  return "queen";
}

const string Queen::toString() const {
  if (color_ == E_Color::WHITE) {
    return "Q";
  } else {
    return "q";
  }
}

/* -------------------------------------------- */
/*                     Rook                     */
/* -------------------------------------------- */
Rook::Rook(int x, int y, E_Color color) : Piece(x, y, color) {}

bool Rook::validate_move(int x, int y, const array<Piece*, 64>& board) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  // check line
  if (y_ == y && x < 7 && x >= 0) {
    return checkLine(x_, x, y, board);
  }

  // check column
  if (x_ == x && y < 7 && y >= 0) {
    return checkColumn(y_, x, y, board);
  }

  return false;
}

bool Rook::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string Rook::getType() {
  return "rook";
}

const string Rook::toString() const {
  if (color_ == E_Color::WHITE) {
    return "R";
  } else {
    return "r";
  }
}

/* -------------------------------------------- */
/*                    Knight                    */
/* -------------------------------------------- */
Knight::Knight(int x, int y, E_Color color) : Piece(x, y, color) {}

bool Knight::validate_move(int x, int y, const array<Piece*, 64>& board) {
  (void)board;
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2))
    return true;

  return false;
}

bool Knight::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string Knight::getType() {
  return "knight";
}

const string Knight::toString() const {
  if (color_ == E_Color::WHITE) {
    return "N";
  } else {
    return "n";
  }
}

/* -------------------------------------------- */
/*                    Bishop                    */
/* -------------------------------------------- */
Bishop::Bishop(int x, int y, E_Color color) : Piece(x, y, color) {}

bool Bishop::validate_move(int x, int y, const array<Piece*, 64>& board) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  // check diagonale
  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY) {
    return checkDiagonals(x_, y_, x, y, board);
  }

  return false;
}

bool Bishop::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string Bishop::getType() {
  return "bishop";
}

const string Bishop::toString() const {
  if (color_ == E_Color::WHITE) {
    return "B";
  } else {
    return "b";
  }
}

/* -------------------------------------------- */
/*                     Pawn                     */
/* -------------------------------------------- */
Pawn::Pawn(int x, int y, E_Color color, bool already_move)
    : Piece(x, y, color), already_move_(already_move) {}

bool Pawn::validate_move(int x, int y, const array<Piece*, 64>& board) {
  if (x > 7 || x < 0 || y > 7 || y < 0)
    return false;

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  for (int i = y_; i <= y; i++) {
    if (board[x_ * 8 + i] != nullptr) {
      return false;
    }
  }

  if (diffX == 0) {
    if (!already_move_) {
      if (diffY == 2 || diffY == 1) {
        return true;
      }
    }

    if (diffY == 1) {
      return true;
    }
  }

  if (diffY == 1 && diffX == 1 && board[x * 8 + y] != 0) {
    return true;
  }

  return false;
}

bool Pawn::move(int x, int y, const array<Piece*, 64>& board) {
  if (validate_move(x, y, board)) {
    already_move_ = true;
    x_ = x;
    y_ = y;
    return true;
  }
  return false;
}

string Pawn::getType() {
  return "pawn";
}

const string Pawn::toString() const {
  if (color_ == E_Color::WHITE) {
    return "P";
  } else {
    return "p";
  }
}

void Pawn::forward() {}

void Pawn::promote() {}
