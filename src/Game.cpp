#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Piece.cpp"
#include "Utils.hpp"

using namespace std;

Game::Game(const string& fen) : historical_() {
  array<Piece*, 64> board = chessboard_.getBoard();
  E_Color actual_player_ = E_Color::WHITE;
  array<bool, 4> castle_rights = chessboard_.getCastle_rights();
  array<int, 2> en_passant = chessboard_.getEnPassant_();

  Utils::parse_fen(fen, board, actual_player_, castle_rights, en_passant);
}

bool Game::check_echec(int x, int y) {
  // E_Color player = actual_player_.getColor();
  array<Piece*, 64> board = chessboard_.getBoard();
  // check ligne
  for (int i = 0; i < 8; i++) {
    if (board[i * 8 + y]->getType() == "queen" ||
        board[i * 8 + y]->getType() == "rook")
      return true;
  }
  // check colomn
  for (int j = y; j < 8; j++) {
    if (board[x * 8 + j]->getType() == "queen" ||
        board[x * 8 + j]->getType() == "rook") {
      return true;
    }
  }
  // check diagonale
  for (int i = x; i < 8; i++) {
    for (int j = y; j >= 0; j--) {
      if (board[i * 8 + j]->getType() == "queen" ||
          board[i * 8 + j]->getType() == "bishop")
        if (x > 7 || x < 0 || y > 7 || y < 0) {
          if (board[i * 8 + j]->getType() == "queen" ||
              board[i * 8 + j]->getType() == "bishop") {
            return true;
          }
        }
    }
  }
  for (int i = x; i < 8; i++) {
    for (int j = y; j < 8; j++) {
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop") {
          return true;
        }
      }
    }
  }
  for (int i = x; i >= 0; i--) {
    for (int j = y; j < 8; j++) {
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop") {
          return true;
        }
      }
    }
  }
  for (int i = x; i >= 0; i--) {
    for (int j = y; j >= 0; j--) {
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop") {
          return true;
        }
      }
    }
  }
  // check Knight

  bool knightright = board[(x + 2) * 8 + (y + 1)]->getType() == "knight" ||
                     board[(x + 2) * 8 + (y - 1)]->getType() == "knight";
  bool knightleft = board[(x - 2) * 8 + (y + 1)]->getType() == "knight" ||
                    board[(x - 2) * 8 + (y - 1)]->getType() == "knight";
  bool knightbot = board[(x + 1) * 8 + (y + 2)]->getType() == "knight" ||
                   board[(x - 1) * 8 + (y + 2)]->getType() == "knight";
  bool knighttop = board[(x + 1) * 8 + (y - 2)]->getType() == "knight" ||
                   board[(x - 1) * 8 + (y - 2)]->getType() == "knight";
  if (knightright || knightleft || knightbot || knighttop)
    return true;

  // check Pawn

  if (board[(x + 1) + (y - 1)]->getType() == "pawn" ||
      board[(x - 1) + (y - 1)]->getType() == "pawn")
    return true;

  // check King
  bool KingRight = board[(x + 1)]->getType() == "king";
  bool KingLeft = board[(x - 1)]->getType() == "king";
  bool KingTop = board[(y + 1)]->getType() == "king";
  bool KingBot = board[(y - 1)]->getType() == "king";
  bool KingTopRight = board[(x + 1) + (y - 1)]->getType() == "king";
  bool KingTopLeft = board[(x - 1) + (y - 1)]->getType() == "king";
  bool KingBotRight = board[(x + 1) + (y + 1)]->getType() == "king";
  bool KingBotLeft = board[(x - 1) + (y + 1)]->getType() == "king";
  if (KingRight || KingLeft || KingTop || KingBot || KingTopRight ||
      KingTopLeft || KingBotRight || KingBotLeft)
    return true;
}
