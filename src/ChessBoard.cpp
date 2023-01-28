#include "ChessBoard.hpp"
#include <iostream>
#include "Piece.hpp"
#include "Utils.hpp"

using namespace std;

ChessBoard::ChessBoard()
    : board_(new int[64]),
      castle_rights_(new bool[4]),
      in_passing_(new int[2]) {
  for (int i = 0; i < 64; i++)
    board_[i] = 0;

  for (int i = 0; i < 4; i++)
    castle_rights_[i] = false;
}

ChessBoard::~ChessBoard() {
  delete[] board_;
}

void ChessBoard::print() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board_[i * 8 + j] != 0) {
        cout << Utils::int_to_char_piece(board_[i * 8 + j]) << " ";
      } else {
        cout << '.' << " ";
      }
    }
    cout << endl;
  }
}