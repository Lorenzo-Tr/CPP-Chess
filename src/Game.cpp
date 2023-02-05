#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game(const string& fen) : actual_player_(), historical_() {
  cout << "Game" << endl;
  players_ = {new Player(chessboard_, "white", E_Color::WHITE),
              new Player(chessboard_, "black", E_Color::BLACK)};

  array<Piece*, 64>& board = chessboard_.getBoard();
  E_Color actual_player;
  array<bool, 4>& castle_rights = chessboard_.getCastle_rights();
  array<int, 2>& en_passant = chessboard_.getEnPassant();

  Utils::parse_fen(fen, board, actual_player, castle_rights, en_passant);

  change_player(actual_player);
}

void Game::change_player(E_Color color) {
  actual_player_ = players_[color];
}

bool Game::check_echec() {
  int kingX, kingY;
  E_Color kingColor = actual_player_->getColor();
  array<Piece*, 64>& board = chessboard_.getBoard();

  for (int i = 0; i < 64; i++) {
    int x = i % 8;
    int y = i / 8;
    Piece* piece = board[y * 8 + x];
    if (piece && piece->getColor() == kingColor) {
      kingX = x;
      kingY = y;
    }
  }

  (void)kingX;
  (void)kingY;

  // return Utils::isUnderAttack(kingX, kingY, kingColor, , board);
  return false;
}

bool Game::check_mat() {
  int kingX, kingY;
  E_Color kingColor = actual_player_->getColor();
  array<Piece*, 64>& board = chessboard_.getBoard();

  for (int i = 0; i < 64; i++) {
    int x = i % 8;
    int y = i / 8;
    Piece* piece = board[y * 8 + x];
    if (piece && piece->getColor() == kingColor) {
      kingX = x;
      kingY = y;
    }
  }

  (void)kingX;
  (void)kingY;

  if (check_echec()) {
    return true;
  }

  return false;
}
