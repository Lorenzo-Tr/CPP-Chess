#include "Player.hpp"

Player::Player(string name, E_Color color) : name_(name), color_(color) {}

string Player::getColor() {
  if (color_ == E_Color::WHITE) {
    return "White";
  }
  return "Black";
}

int Player::play_move(int x1, int y1, int x2, int y2) {}

int Player::read_move() {
  string move;
  cout << getColor() << " : Enter your move \"x y\": " << endl;
  getline(cin, move);
}
