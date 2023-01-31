#pragma once

#include <array>
#include <string>
#include "E_Color.hpp"

using namespace std;

class Piece {
 protected:
  int x_;
  int y_;
  E_Color color_;

 public:
  Piece(int x, int y, E_Color color);

  bool operator!=(const string&);
  friend ostream& operator<<(ostream& os, const Piece& p);

  virtual string getType();
  virtual const string toString() const;
  // Check if is a valid move
  virtual bool validate_move(int x, int y, const array<Piece*, 64>& board) = 0;
  // Move Piece if is a valid move
  virtual void move(int x, int y, const array<Piece*, 64>& board) = 0;
};

class King : public Piece {
 public:
  King(int x, int y, E_Color color);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;
};

class Queen : public Piece {
 public:
  Queen(int x, int y, E_Color color);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;
};

class Rook : public Piece {
 public:
  Rook(int x, int y, E_Color color);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;
};

class Knight : public Piece {
 public:
  Knight(int x, int y, E_Color color);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;
};

class Bishop : public Piece {
 public:
  Bishop(int x, int y, E_Color color);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;
};

class Pawn : public Piece {
 private:
  bool already_move_;

 public:
  Pawn(int x, int y, E_Color color, bool already_move);
  bool validate_move(int x, int y, const array<Piece*, 64>& board);
  void move(int x, int y, const array<Piece*, 64>& board);
  string getType();
  string const toString() const;

  void forward();
  void promote();
};
