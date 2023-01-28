#pragma once

class ChessBoard {
 private:
  int* board_;
  bool* castle_rights_;
  int* in_passing_;

 public:
  ChessBoard();
  ~ChessBoard();

  inline int* getBoard() { return board_; }
  inline bool* getCastle_rights() { return castle_rights_; }
  inline int* getInPassing() { return in_passing_; }

  void print();
  // Check if the move is valide
  bool check_move(int x1, int y1, int x2, int y2);
  // Play a move if is a valide move
  bool play_move(int x1, int y1, int x2, int y2);
};