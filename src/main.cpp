#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
  Game game;
  array<int, 4> move;

  while (1) {
    game.GetChessBoard().print();
    cout << endl;
    move = game.GetActualPlayer()->read_move();
    game.GetActualPlayer()->play_move(move[0], move[1], move[2], move[3]);
    E_Color turn = game.GetActualPlayer()->getColor() == WHITE ? WHITE : BLACK;
    game.change_player(turn);
  }

  return 0;
}