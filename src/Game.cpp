#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") : chessboard_(), historical_() {
  int* board = chessboard_.getBoard();
  E_Color actual_player_ = E_Color::WHITE;
  bool* castle_rights = chessboard_.getCastle_rights();

  Utils::parse_fen(fen, board, &actual_player_, castle_rights);
}