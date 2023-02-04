#include "Utils.hpp"
#include <iostream>

using namespace std;

Piece* Utils::char_to_piece(int index, char letter) {
  Piece* value;
  int x = index % 8;
  int y = index / 8;

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
    default:
      value = nullptr;
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
  ++it;
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

void Utils::clear() {
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

bool Utils::isUnderAttackByPawn(int x,
                                int y,
                                E_Color color,
                                const array<Piece*, 64>& board) {
  int dx[] = {-1, 1};
  int dy[] = {-1, 1};

  for (int i = 0; i < 2; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 &&
        board[ny * 8 + nx] != nullptr &&
        board[ny * 8 + nx]->getType() == "pawn" &&
        board[ny * 8 + nx]->getColor() != color) {
      return true;
    }
  }

  return false;
}

bool Utils::isUnderAttackByKnight(int x,
                                  int y,
                                  E_Color color,
                                  const array<Piece*, 64>& board) {
  int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
  int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 &&
        board[ny * 8 + nx] != nullptr &&
        board[ny * 8 + nx]->getType() == "knight" &&
        board[ny * 8 + nx]->getColor() != color) {
      return true;
    }
  }
  return false;
}

bool Utils::isUnderAttackHorizontalOrVertical(int x,
                                              int y,
                                              E_Color color,
                                              const array<Piece*, 64>& board) {
  // Check horizontal attack
  for (int i = 0; i < 8; i++) {
    if (i == y)
      continue;
    if (board[x * 8 + i] != nullptr && board[x * 8 + i]->getColor() != color &&
        (board[x * 8 + i]->getType() == "rook" ||
         board[x * 8 + i]->getType() == "queen"))
      return true;
  }

  // Check vertical attack
  for (int i = 0; i < 8; i++) {
    if (i == x)
      continue;
    if (board[i * 8 + y] != nullptr && board[i * 8 + y]->getColor() != color &&
        (board[i * 8 + y]->getType() == "rook" ||
         board[i * 8 + y]->getType() == "queen"))
      return true;
  }

  return false;
}

bool Utils::isUnderAttackDiagonal(int x,
                                  int y,
                                  E_Color color,
                                  const array<Piece*, 64>& board) {
  // Check left-up diagonal
  for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
    Piece* piece = board[i * 8 + j];
    if (piece &&
        (piece->getType() == "bishop" || piece->getType() == "queen") &&
        piece->getColor() != color) {
      return true;
    }
    if (piece) {
      break;
    }
  }

  // Check right-up diagonal
  for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
    Piece* piece = board[i * 8 + j];
    if (piece &&
        (piece->getType() == "bishop" || piece->getType() == "queen") &&
        piece->getColor() != color) {
      return true;
    }
    if (piece) {
      break;
    }
  }

  // Check left-down diagonal
  for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
    Piece* piece = board[i * 8 + j];
    if (piece &&
        (piece->getType() == "bishop" || piece->getType() == "queen") &&
        piece->getColor() == color) {
      return true;
    }
    if (piece) {
      break;
    }
  }

  // Check right-down diagonal
  for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
    Piece* piece = board[i * 8 + j];
    if (piece &&
        (piece->getType() == "bishop" || piece->getType() == "queen") &&
        piece->getColor() == color) {
      return true;
    }
    if (piece) {
      break;
    }
  }
  return false;
}

bool Utils::isUnderAttack(int x,
                          int y,
                          E_Color color,
                          const array<Piece*, 64>& board) {
  bool pawn = isUnderAttackByPawn(x, y, color, board);
  bool knight = isUnderAttackByKnight(x, y, color, board);
  bool diagonals = isUnderAttackDiagonal(x, y, color, board);
  bool line_col = isUnderAttackHorizontalOrVertical(x, y, color, board);

  return pawn || knight || diagonals || line_col;
}