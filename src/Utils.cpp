#include "Utils.hpp"
#include <iostream>

using namespace std;

char Utils::int_to_char_piece(int value) {
  char letter;
  int tmp_value;

  tmp_value = value > 10 ? value - 10 : value;

  switch (tmp_value) {
    case 1:
      letter = 'r';  // Rook
      break;
    case 2:
      letter = 'n';  // Knight
      break;
    case 3:
      letter = 'b';  // Bishop
      break;
    case 4:
      letter = 'q';  // Queen
      break;
    case 5:
      letter = 'k';  // King
      break;
    case 6:
      letter = 'p';  // Pawn
      break;
  }

  if (value > 10)
    return toupper(letter);

  return letter;
}

int Utils::char_to_int_piece(char letter) {
  int value;

  switch (letter) {
    case 'r':
      value = 1;  // Rook
      break;
    case 'n':
      value = 2;  // Knight
      break;
    case 'b':
      value = 3;  // Bishop
      break;
    case 'q':
      value = 4;  // Queen
      break;
    case 'k':
      value = 5;  // King
      break;
    case 'p':
      value = 6;  // Pawn
      break;
    case 'R':
      value = 11;  // Rook
      break;
    case 'N':
      value = 12;  // Knight
      break;
    case 'B':
      value = 13;  // Bishop
      break;
    case 'Q':
      value = 14;  // Queen
      break;
    case 'K':
      value = 15;  // King
      break;
    case 'P':
      value = 16;  // Pawn
      break;
  }

  return value;
}

void Utils::move_iterator(string::const_iterator it) {
  while (*it == ' ')
    it++;
}

string::const_iterator Utils::parse_board(string::const_iterator it,
                                          string::const_iterator end,
                                          int* board) {
  int i = 0;
  while (it != end) {
    if (*it == ' ')
      break;

    if (*it == '/') {
      it++;
      continue;
    }

    if (isdigit(*it)) {
      i += (*it - '0');  // converts char digit to int. `5` to 5
    } else {
      board[i] = char_to_int_piece(*it);
      ++i;
    }
    it++;
  }
  move_iterator(++it);
  return it;
}

string::const_iterator Utils::parse_turn(string::const_iterator it,
                                         E_Color* turn) {
  *turn = *it == 'w' ? E_Color::WHITE : E_Color::BLACK;
  move_iterator(++it);
  return it;
}

string::const_iterator Utils::parse_castle_rights(string::const_iterator it,
                                                  string::const_iterator end,
                                                  bool* castle_rights) {
  while ((it != end)) {
    switch (*it) {
      case 'k':
        castle_rights[E_Color::BLACK] = true;
        break;
      case 'K':
        castle_rights[E_Color::WHITE] = true;
        break;
      case 'q':
        castle_rights[E_Color::BLACK + 2] = true;
        break;
      case 'Q':
        castle_rights[E_Color::WHITE + 2] = true;
        break;
    }
    it++;
  }

  move_iterator(it);
  return it;
}

void Utils::parse_fen(const string& fen_code,
                      int* board,
                      E_Color* turn,
                      bool* castle_rights) {
  auto it = fen_code.begin();
  auto end = fen_code.end();

  it = parse_board(it, end, board);
  it = parse_turn(it, turn);
  it = parse_castle_rights(it, end, castle_rights);
  // en_passant = fen_code.substr(*it, 3);
}