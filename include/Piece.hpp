#pragma once

class Piece {
 private:
  bool color_;
  int x_;
  int y_;

 public:
  Piece(int x, int y, bool color);

  // Check if is a valid move
  virtual bool validate_move(int x, int y) = 0;
  // Move Piece if is a valid move
  virtual void move(int x, int y) = 0;
};

class King : public Piece {
 public:
  King(int x, int y, bool color);
  bool validate_move(int x, int y);
  void move(int x, int y);
};

class Queen : public Piece {
 public:
  Queen(int x, int y, bool color);
  bool validate_move(int x, int y);
  void move(int x, int y);
};

class Rook : public Piece {
 public:
  Rook(int x, int y, bool color);
  bool validate_move(int x, int y);
  void move(int x, int y);
};

class Knight : public Piece {
 public:
  Knight(int x, int y, bool color);
  bool validate_move(int x, int y);
  void move(int x, int y);
};

class Bishop : public Piece {
 public:
  Bishop(int x, int y, bool color);
  bool validate_move(int x, int y);
  void move(int x, int y);
};

class Pawn : public Piece {
 private:
  bool can_move_;

 public:
  Pawn(int x, int y, bool color, bool can_move);
  bool validate_move(int x, int y);
  void move(int x, int y);
  void forward();
  void promote();
};