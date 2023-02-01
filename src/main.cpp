#include <iostream>
#include "Game.hpp"

using namespace std;

int main() {
  Game game;

  while (1) {
    game.GetChessBoard().print();
    cout << endl;
    game.GetActualPlayer().read_move();
  }

  return 0;
}