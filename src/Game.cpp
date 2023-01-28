#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game() : chessboard_(), historical_() {
  // string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  string fen =
      "rnbqkbnr/ppp1pp1p/6p1/3p4/5P2/2N1P3/PPPP2PP/R1BQKBNR w KQkq - 0 1";
  int* board = chessboard_.getBoard();
  E_Color actual_player_ = E_Color::WHITE;
  bool* castle_rights = chessboard_.getCastle_rights();

  Utils::parse_fen(fen, board, &actual_player_, castle_rights);
}