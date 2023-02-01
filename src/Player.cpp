#include "Player.hpp"
#include <string.h>
#include <sstream>
#include <vector>

using namespace std;

Player::Player() : name_(), color_(E_Color::NONE) {}
Player::Player(string name, E_Color color) : name_(name), color_(color) {}

int Player::play_move(int x1, int y1, int x2, int y2) {
  (void)x1;
  (void)y1;
  (void)x2;
  (void)y2;
  return 0;
}

array<int, 4> Player::read_move() {
  string move;
  bool read = true;
  array<int, 4> coordinate;
  bool from = true;

  while (read) {
    const string& text = from ? " : Enter the piece you want to move \"x y\": "
                              : " : Enter where want to move \"x y\": ";
    cout << getColor() << text << endl;
    int i = from ? 0 : 2;

    getline(cin, move);
    istringstream iss(move);
    int x, y;
    if (!(iss >> x >> y) || x < 0 || x > 7 || y < 0 || y > 7) {
      cout << "Invalid position, the values should be between 0 and 7." << endl;
      continue;
    }

    coordinate[i] = x;
    coordinate[i + 1] = y;
    if (from) {
      from = false;
      continue;
    }

    read = false;
  }

  for (auto it = coordinate.begin(); it != coordinate.end(); ++it) {
    cout << *it << endl;
  }

  return coordinate;
}
