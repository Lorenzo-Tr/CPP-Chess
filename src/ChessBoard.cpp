#include "ChessBoard.hpp"
#include <iostream>
#include <typeinfo>
#include "Piece.hpp"
#include "Utils.hpp"
#include "cstdlib"

using namespace std;

void clear() {
#if defined _WIN32
  system("cls");
  // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
  // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
  system("clear");
#endif
}

ChessBoard::ChessBoard() : board_(), castle_rights_(), en_passant_() {
  for (int i = 0; i < 4; i++)
    castle_rights_[i] = false;
}

void ChessBoard::print() {
  // clear();
  cout << endl;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board_[i * 8 + j] != 0) {
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