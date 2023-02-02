#include "ChessBoard.hpp"
#include <iostream>
#include <typeinfo>
#include "Piece.hpp"
#include "Utils.hpp"
#include "cstdlib"

using namespace std;

ChessBoard::ChessBoard() : board_(), castle_rights_(), en_passant_() {
  for (size_t i = 0; i < 64; i++) {
    board_[i] = nullptr;
  }

  for (int i = 0; i < 4; i++)
    castle_rights_[i] = false;
}

bool ChessBoard::check_move(int x1, int y1, int x2, int y2) {
  (void)x1;
  (void)y1;
  (void)x2;
  (void)y2;
  return true;
}

bool ChessBoard::play_move(int x1, int y1, int x2, int y2) {
  cout << board_[6 * 8 + 6] << " - " << board_[5 * 8 + 6] << endl;

  if (check_move(x1, y1, x2, y2)) {
    if (board_[y1 * 8 + x1]->move(x2, y2, board_)) {
      board_[y2 * 8 + x2] = board_[y1 * 8 + x1];
      board_[y1 * 8 + x1] = nullptr;
      return true;
    } else {
      cout << "Invalid move !" << endl;
    }
  }
  return false;
}

void ChessBoard::print() {
  cout << endl;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board_[i * 8 + j] != nullptr) {
        cout << *board_[i * 8 + j] << " ";
      } else {
        cout << ". ";
      }
    }
    cout << "  " << i << endl;
  }

  cout << endl;
  for (int j = 0; j < 8; j++) {
    cout << j << " ";
  }
  cout << endl;
}

void ChessBoard::print_playable_move(int x, int y) {
  cout << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int index = i * 8 + j;
      if (board_[index] != nullptr) {
        if (board_[y * 8 + x]->validate_move(j, i, board_)) {
          cout << "#" << *board_[index];
        } else {
          cout << *board_[index] << " ";
        }
      } else {
        if (board_[y * 8 + x]->validate_move(j, i, board_)) {
          cout << "# ";
        } else {
          cout << ". ";
        }
      }
    }
    cout << "  " << i << endl;
  }
  cout << endl;
  for (int j = 0; j < 8; j++) {
    cout << j << " ";
  }
  cout << endl;
}