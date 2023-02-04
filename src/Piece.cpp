#include "Piece.hpp"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "Utils.hpp"

using namespace std;

bool checkDiagonals(int x1,
                    int y1,
                    int x2,
                    int y2,
                    const array<Piece*, 64>& board) {
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

bool checkLine(int x1, int y1, int y2, const array<Piece*, 64>& board) {
  int min_y = min(y1, y2);
  int max_y = max(y1, y2);
  for (int y = min_y + 1; y < max_y; y++) {
    if (board[y * 8 + x1] != nullptr) {
      return false;
    }
  }
  return true;
}

bool checkColumn(int x1, int y1, int x2, const array<Piece*, 64>& board) {
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
Piece::Piece(int x, int y, E_Color color) : x_(x), y_(y), color_(color) {}

Piece::~Piece() {}

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
King::~King() {}

bool King::validate_move(int x, int y, const array<Piece*, 64>& board) {
  // (void)board;

  // Check if the new position is one square vertically
  if (abs(x - x_) == 1 && y_ == y) {
    return !Utils::isUnderAttack(x, y, color_, board);
  }
  // Check if the new position is one square horizontally
  if (abs(y - y_) == 1 && x_ == x) {
    return !Utils::isUnderAttack(x, y, color_, board);
  }
  // Check if the new position is one square diagonally
  if (abs(x - x_) == 1 && abs(y - y_) == 1) {
    return !Utils::isUnderAttack(x, y, color_, board);
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

bool Queen::validate_move(int x, int y, const array<Piece*, 64>& board) {
  // check line
  if (x_ == x) {
    return checkLine(x_, y_, y, board);
  }

  // check column
  if (y_ == y) {
    return checkColumn(x_, y_, x, board);
  }

  // check diagonale
  if (abs(x - x_) == abs(y - y_)) {
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
Rook::~Rook() {}

bool Rook::validate_move(int x, int y, const array<Piece*, 64>& board) {
  // check line
  if (x_ == x) {
    return checkLine(x_, y_, y, board);
  }

  // check column
  if (y_ == y) {
    return checkColumn(x_, y_, x, board);
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

bool Knight::validate_move(int x, int y, const array<Piece*, 64>& board) {
  auto dest_piece = board[y * 8 + x];

  if (checkKnight(abs(x_ - x), abs(y_ - y))) {
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
Bishop::~Bishop() {}

bool Bishop::validate_move(int x, int y, const array<Piece*, 64>& board) {
  // check diagonale
  if (abs(x - x_) == abs(y - y_)) {
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
Pawn::~Pawn() {}

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
