#include "ChessBoard.hpp"
#include <iostream>
#include <typeinfo>
#include "Piece.hpp"
#include "Utils.hpp"

using namespace std;

ChessBoard::ChessBoard() : board_(), castle_rights_(), in_passing_() {
  for (int i = 0; i < 4; i++)
    castle_rights_[i] = false;
}

void ChessBoard::print() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << board_[i * 8 + j] << " ";
    }
    cout << endl;
  }
}