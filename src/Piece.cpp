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
    if (board[y * 8 + i] != 0) {
      return false;
    }
  }
  return true;
}

bool checkColumn(int y_, int x, int y, const array<Piece*, 64>& board) {
  for (int j = y_; j <= y; j++) {
    if (board[j * 8 + x] != 0) {
      return false;
    }
  }
  return true;
}

bool checkKnight(int diffX, int diffY) {
  if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2)) {
    return true;
  }

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

void King::move(int x, int y) {
  x_ = x;
  y_ = y;
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

void Queen::move(int x, int y) {
  x_ = x;
  y_ = y;
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

void Rook::move(int x, int y) {
  x_ = x;
  y_ = y;
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
  if (x > 7 || x < 0 || y > 7 || y < 0) {
    return false;
  }

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  if ((diffX == 2 && diffY == 1) || (diffX == 1 && diffY == 2)) {
    auto dest_piece = board[y * 8 + x];
    return dest_piece == nullptr || dest_piece->getColor() != color_;
  }

  return false;
}

void Knight::move(int x, int y) {
  x_ = x;
  y_ = y;
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
  if (x > 7 || x < 0 || y > 7 || y < 0) {
    return false;
  }

  int diffX = abs(x_ - x);
  int diffY = abs(y_ - y);

  // check diagonale
  if (diffX >= 0 && diffX < 7 && diffY >= 0 && diffY < 7 && diffX == diffY) {
    return checkDiagonals(x_, y_, x, y, board);
  }

  return false;
}

void Bishop::move(int x, int y) {
  x_ = x;
  y_ = y;
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
  int diffX = abs(x - x_);
  int diffY = abs(y - y_);

  if (diffX > 1 || (diffX == 1 && board[y * 8 + x] == nullptr)) {
    return false;
  }

  bool is_forward = color_ == WHITE ? y < y_ : y > y_;
  if (!is_forward) {
    return false;
  }

  if (diffY == 2 && !already_move_) {
    int forward_y = y_ + (color_ == WHITE ? -1 : 1);
    if (board[forward_y * 8 + x_] != nullptr) {
      return false;
    }
  } else if (diffY == 1) {
    if (diffX == 1) {
      if (board[y * 8 + x]->getColor() == (color_ == WHITE ? BLACK : WHITE)) {
        return true;
      } else {
        return false;
      }
    } else if (board[y * 8 + x_] != nullptr) {
      return false;
    }
  } else {
    return false;
  }

  return true;
}

void Pawn::move(int x, int y) {
  already_move_ = true;
  x_ = x;
  y_ = y;
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