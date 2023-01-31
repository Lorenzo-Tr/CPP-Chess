#include "Utils.hpp"
#include <iostream>

using namespace std;

Piece* Utils::char_to_piece(int index, char letter) {
  Piece* value;
  int x, y;
  for (y = 0; y < 8; y++) {
    for (x = 0; x < 8; x++) {
      if ((y + 1) * x == index) {
        break;
      }
    }
  }

  switch (letter) {
    case 'r':
      value = new Rook(x, y, E_Color::BLACK);  // Rook
      break;
    case 'n':
      value = new Knight(x, y, E_Color::BLACK);  // Knight
      break;
    case 'b':
      value = new Bishop(x, y, E_Color::BLACK);  // Bishop
      break;
    case 'q':
      value = new Queen(x, y, E_Color::BLACK);  // Queen
      break;
    case 'k':
      value = new King(x, y, E_Color::BLACK);  // King
      break;
    case 'p':
      value = new Pawn(x, y, E_Color::BLACK, false);  // Pawn
      break;
    case 'R':
      value = new Rook(x, y, E_Color::WHITE);  // Rook
      break;
    case 'N':
      value = new Knight(x, y, E_Color::WHITE);  // Knight
      break;
    case 'B':
      value = new Bishop(x, y, E_Color::WHITE);  // Bishop
      break;
    case 'Q':
      value = new Queen(x, y, E_Color::WHITE);  // Queen
      break;
    case 'K':
      value = new King(x, y, E_Color::WHITE);  // King
      break;
    case 'P':
      value = new Pawn(x, y, E_Color::WHITE, false);  // Pawn
      break;
  }

  return value;
}

string::const_iterator Utils::parse_board(std::string::const_iterator it,
                                          std::string::const_iterator end,
                                          std::array<Piece*, 64>& board) {
  int index = 0;
  while (it != end && *it != ' ') {
    if (*it == '/') {
      ++it;
      continue;
    }

    if (isdigit(*it)) {
      index += *it - '0';
    } else {
      board[index] = char_to_piece(index, *it);
      index++;
    }
    ++it;
  }
  it++;
  return it;
}

string::const_iterator Utils::parse_turn(std::string::const_iterator it,
                                         E_Color& turn) {
  turn = *it == 'w' ? E_Color::WHITE : E_Color::BLACK;
  ++it;
  return it;
}

string::const_iterator Utils::parse_castle_rights(
    std::string::const_iterator it,
    std::string::const_iterator end,
    std::array<bool, 4>& castle_rights) {
  castle_rights.fill(false);
  while (it != end && *it != ' ') {
    switch (*it) {
      case 'k':
        castle_rights[0] = true;
        break;
      case 'K':
        castle_rights[1] = true;
        break;
      case 'q':
        castle_rights[2] = true;
        break;
      case 'Q':
        castle_rights[3] = true;
        break;
    }
    ++it;
  }
  return it;
}

string::const_iterator Utils::parse_en_passant(string::const_iterator it,
                                               array<int, 2>& en_passant) {
  if (*it == '-') {
    en_passant[0] = -1;
    en_passant[1] = -1;
  } else {
    en_passant[0] = 8 * (8 - (*(it + 1) - '0')) + (*it - 'a');
    en_passant[1] = *(it + 2) == 'w' ? 1 : 0;
  }
  move_iterator(it + 3);
  return it + 3;
}

void Utils::parse_fen(const string& fen_code,
                      array<Piece*, 64>& board,
                      E_Color& turn,
                      array<bool, 4>& castle_rights,
                      array<int, 2>& en_passant) {
  auto it = fen_code.begin();
  auto end = fen_code.end();

  it = parse_board(it, end, board);
  it = parse_turn(it, turn);
  it = parse_castle_rights(it, end, castle_rights);
  it = parse_en_passant(it, en_passant);
}