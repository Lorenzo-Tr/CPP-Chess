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