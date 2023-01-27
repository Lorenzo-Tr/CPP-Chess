#include "Game.hpp"

Game::Game(ChessBoard board, bool player, list<string> historical)
    : chessboard_(board),
      actual_player_(player),
      historical_shots_(historical) {}