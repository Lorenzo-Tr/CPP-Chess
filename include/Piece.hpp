#pragma once

#include <array>
#include <string>
#include <vector>
#include "E_Color.hpp"

using namespace std;

struct Move {
  const int StartSquare;
  const int TargetSquare;
  Move(int s, int t) : StartSquare(s), TargetSquare(t) {}
};

class Piece {
 protected:
  int x_;
  int y_;
  E_Color color_;
  vector<Move*> pseudoLegalMoves_;

 public:
  typedef const array<Piece*, 64>& board;
  Piece(int x, int y, E_Color color);
  virtual ~Piece();

  bool operator!=(const string&);
  friend ostream& operator<<(ostream& os, const Piece& p);

  inline E_Color getColor() {
    if (getType() == "") {
      return E_Color::NONE;
    }
    return color_;
  }
  inline int getY() { return y_; }
  inline vector<Move*>& getPseudoLegalMoves() { return pseudoLegalMoves_; }
  virtual string getType();
  virtual const string toString() const;
  // Check if is a valid move
  virtual bool isPseudoLegalMove(int x, int y) = 0;
  // Move Piece if is a valid move
  virtual void move(int x, int y) = 0;
};

class King : public Piece {
 public:
  King(int x, int y, E_Color color);
  virtual ~King();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  vector<Move> generateMoves();
  string getType();
  string const toString() const;
};

class Queen : public Piece {
 public:
  Queen(int x, int y, E_Color color);
  virtual ~Queen();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  vector<Move> generateMoves();
  string getType();
  string const toString() const;
};

class Rook : public Piece {
 public:
  Rook(int x, int y, E_Color color);
  virtual ~Rook();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  vector<Move> generateMoves();
  string getType();
  string const toString() const;
};

class Knight : public Piece {
 public:
  Knight(int x, int y, E_Color color);
  virtual ~Knight();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  vector<Move> generateMoves();
  string getType();
  string const toString() const;
};

class Bishop : public Piece {
 public:
  Bishop(int x, int y, E_Color color);
  virtual ~Bishop();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  vector<Move> generateMoves();
  string getType();
  string const toString() const;
};

class Pawn : public Piece {
 private:
  bool already_move_;

 public:
  Pawn(int x, int y, E_Color color, bool already_move);
  virtual ~Pawn();
  bool isPseudoLegalMove(int x, int y);
  void move(int x, int y);
  inline bool isAlreadyMove() { return already_move_; }
  vector<Move> generateMoves();
  string getType();
  string const toString() const;

  Piece* promote();
};
