#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game(const string& fen) : historical_() {
  array<Piece*, 64> board = chessboard_.getBoard();
  E_Color actual_player_ = E_Color::WHITE;
  array<bool, 4> castle_rights = chessboard_.getCastle_rights();
  array<int, 2> en_passant = chessboard_.getEnPassant_();

  Utils::parse_fen(fen, board, actual_player_, castle_rights, en_passant);
}