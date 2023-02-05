#include <iostream>
#include "Game.hpp"
#include "Utils.hpp"

using namespace std;

int main() {
  Game game("1n1k1b2/8/6p1/3Q4/8/8/3K4/8 b - - 0 1");
  // Game game;
  array<int, 4> move;

  while (1) {
    game.GetChessBoard().print();
    game.GetChessBoard().generateMoves(game.GetActualPlayer()->getColor());
    move = game.GetActualPlayer()->read_move();
    game.GetActualPlayer()->play_move(move[0], move[1], move[2], move[3]);
    game.change_player();
  }

  return 0;
}