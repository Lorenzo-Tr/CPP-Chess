#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game(const string& fen) : actual_player_(), historical_() {
  players_[E_Color::WHITE] = new Player("white", E_Color::WHITE);
  players_[E_Color::BLACK] = new Player("black", E_Color::BLACK);

  array<Piece*, 64> board = chessboard_.getBoard();
  E_Color actual_player = E_Color::WHITE;
  array<bool, 4> castle_rights = chessboard_.getCastle_rights();
  array<int, 2> en_passant = chessboard_.getEnPassant();

  Utils::parse_fen(fen, board, actual_player, castle_rights, en_passant);
  chessboard_.setBoard(board);
  change_player(actual_player);
  chessboard_.setCastleRights(castle_rights);
  chessboard_.setEnPassant(en_passant);
}

void Game::change_player(E_Color color) {
  actual_player_ = *players_[color];
}

bool Game::check_echec(int x, int y) {
  E_Color player = actual_player_.getColor();
  array<Piece*, 64> board = chessboard_.getBoard();
  // check ligne
  for (int i = 0; i < 8; i++) {
    int diffx = abs(i - x);

    if (board[i * 8 + y]->getType() == "queen" ||
        board[i * 8 + y]->getType() == "rook" ||
        (board[i * 8 + y]->getType() == "king" && (diffx == 1)))
      return true;
  }
  // check colomn
  for (int j = y; j < 8; j++) {
    int diffy = abs(j - y);
    if (board[x * 8 + j]->getType() == "queen" ||
        board[x * 8 + j]->getType() == "rook" ||
        (board[x * 8 + j]->getType() == "king" && (diffy == 1))) {
      return true;
    }
  }
  // check diagonale
  for (int i = x; i < 8; i++) {
    for (int j = y; j >= 0; j--) {
      int diffx = abs(i - x);
      int diffy = abs(j - y);
      if (board[i * 8 + j]->getType() == "queen" ||
          board[i * 8 + j]->getType() == "bishop" ||
          (board[i * 8 + j]->getType() == "king" && (diffx && diffy == 1)) ||
          (player == board[i * 8 + j]->getColor() &&
           board[i * 8 + j]->getType() == "pawn"))
        if (x > 7 || x < 0 || y > 7 || y < 0) {
          return true;
        }
    }
  }
  for (int i = x; i < 8; i++) {
    for (int j = y; j < 8; j++) {
      int diffx = abs(i - x);
      int diffy = abs(j - y);
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop" ||
            (board[i * 8 + j]->getType() == "king" && (diffx && diffy == 1))) {
          return true;
        }
      }
    }
  }
  for (int i = x; i >= 0; i--) {
    for (int j = y; j < 8; j++) {
      int diffx = abs(i - x);
      int diffy = abs(j - y);
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop" ||
            (board[i * 8 + j]->getType() == "king" && (diffx && diffy == 1))) {
          return true;
        }
      }
    }
  }
  for (int i = x; i >= 0; i--) {
    for (int j = y; j >= 0; j--) {
      int diffx = abs(i - x);
      int diffy = abs(j - y);
      if (x > 7 || x < 0 || y > 7 || y < 0) {
        if (board[i * 8 + j]->getType() == "queen" ||
            board[i * 8 + j]->getType() == "bishop" ||
            (board[i * 8 + j]->getType() == "king" &&
             (diffx && diffy == 1))(player == board[i * 8 + j]->getColor() &&
                                    board[i * 8 + j]->getType() == "pawn")) {
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

  return false;
}
