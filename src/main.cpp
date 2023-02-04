#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
  // Game game("2k5/6P1/8/8/8/8/1p6/5K2 w - - 0 1");
  Game game;
  array<int, 4> move;

  while (1) {
    game.GetChessBoard().print();
    move = game.GetActualPlayer()->read_move();
    game.GetActualPlayer()->play_move(move[0], move[1], move[2], move[3]);
    E_Color turn = game.GetActualPlayer()->getColor() == WHITE ? WHITE : BLACK;
    game.change_player(turn);
  }

  return 0;
}