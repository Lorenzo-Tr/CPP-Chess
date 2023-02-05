#include "Piece.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Game.hpp"
#include "Utils.hpp"

using namespace std;

bool checkDiagonals(int x1, int y1, int x2, int y2, board board) {
  int dx = (x1 < x2) ? 1 : -1;
  int dy = (y1 < y2) ? 1 : -1;
  int x = x1 + dx;
  int y = y1 + dy;
  while (x != x2 && y != y2) {
    if (board[y * 8 + x] != nullptr) {
      return false;
    }
    x += dx;
    y += dy;
  }
  return true;
}

bool checkLine(int x1, int y1, int y2, board board) {
  int min_y = min(y1, y2);
  int max_y = max(y1, y2);
  for (int y = min_y + 1; y < max_y; y++) {
    if (board[y * 8 + x1] != nullptr) {
      return false;
    }
  }
  return true;
}

bool checkColumn(int x1, int y1, int x2, board board) {
  int min_x = min(x1, x2);
  int max_x = max(x1, x2);
  for (int x = min_x + 1; x < max_x; x++) {
    if (board[y1 * 8 + x] != nullptr) {
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
Piece::Piece(int x, int y, E_Color color)
    : x_(x), y_(y), color_(color), pseudoLegalMoves_() {
  // Reserve the max pseudoLegalMoves possible to reduce the number of alloc
  pseudoLegalMoves_.reserve(28);
}

Piece::~Piece() {}

string Piece::getType() {
  return "";
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
King::~King() {}

bool King::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
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
Queen::~Queen() {}

bool Queen::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
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
Rook::~Rook() {}

bool Rook::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
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
Knight::~Knight() {}

bool Knight::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
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
Bishop::~Bishop() {}

bool Bishop::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
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
Pawn::~Pawn() {}

bool Pawn::isPseudoLegalMove(int x, int y) {
  int TargetIndex = y * 8 + x;

  for (auto it : pseudoLegalMoves_) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
  }

  return false;
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

Piece* Pawn::promote() {
  int rank = color_ == WHITE ? 0 : 7;
  if (y_ != rank) {
    return nullptr;
  }

  Piece* promoted_piece = nullptr;
  while (promoted_piece == nullptr) {
    cout << "Choose a piece to promote the pawn to (Q, R, B, N): ";
    string line;
    char piece_char;
    getline(cin, line);
    istringstream iss(line);
    iss >> piece_char;
    switch (toupper(piece_char)) {
      case 'Q':
        promoted_piece = new Queen(x_, y_, color_);
        break;
      case 'R':
        promoted_piece = new Rook(x_, y_, color_);
        break;
      case 'B':
        promoted_piece = new Bishop(x_, y_, color_);
        break;
      case 'N':
        promoted_piece = new Knight(x_, y_, color_);
        break;
      default:
        cout << "Invalid piece choice. Try again." << endl;
        break;
    }
  }

  return promoted_piece;
}
