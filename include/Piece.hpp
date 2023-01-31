#pragma once

#include <array>
#include <string>
#include "ChessBoard.hpp"
#include "E_Color.hpp"

using namespace std;

class Piece {
 private:
  int x_;
  int y_;
  E_Color color_;
  ChessBoard* board_;

 public:
  Piece(int x, int y, E_Color color, ChessBoard* board);

  bool operator!=(const string&);
  friend ostream& operator<<(ostream& os, const Piece& p);

  inline E_Color getColor() const { return color_; }
  inline array<Piece*, 64> getBoard() const { return board_->getBoard(); }
  inline int getX() const { return x_; }
  inline int getY() const { return y_; }

  inline void setColor(E_Color color) { color_ = color; };
  inline void setX(int x) { x_ = x; };
  inline void setY(int y) { y_ = y; };
  inline void setBoard(ChessBoard* board) { board_ = board; }

  virtual string getType();
  virtual const string to_string() const;
  // Check if is a valid move
  virtual bool validate_move(int x, int y) = 0;
  // Move Piece if is a valid move
  virtual void move(int x, int y) = 0;
};

class King : public Piece {
 public:
  King(int x, int y, E_Color color, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;
};

class Queen : public Piece {
 public:
  Queen(int x, int y, E_Color color, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;
};

class Rook : public Piece {
 public:
  Rook(int x, int y, E_Color color, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;
};

class Knight : public Piece {
 public:
  Knight(int x, int y, E_Color color, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;
};

class Bishop : public Piece {
 public:
  Bishop(int x, int y, E_Color color, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;
};

class Pawn : public Piece {
 private:
  bool already_move_;

 public:
  Pawn(int x, int y, E_Color color, bool already_move, ChessBoard* board);
  bool validate_move(int x, int y);
  void move(int x, int y);
  string getType();
  string const to_string() const;

  void forward();
  void promote();
};
