#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
  // Game game(
  //     "r1bqkbnr/pppp1ppp/2n5/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR w KQkq - 0 1");
  Game game("b7/8/3k4/1n5R/8/3K4/8/8 w - - 0 1");
  // Game game;
  array<int, 4> move;

  while (1) {
    game.GetChessBoard().print();
    move = game.GetActualPlayer()->read_move();
    game.GetActualPlayer()->play_move(move[0], move[1], move[2], move[3]);
    E_Color turn = game.GetActualPlayer()->getColor() == WHITE ? BLACK : WHITE;
    game.change_player(turn);
  }

  return 0;
}