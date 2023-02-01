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

array<int, 2> Player::read_move() {
  string move;
  bool read = true;
  char* token;
  array<int, 2> coordinate;

  cout << getColor() << " : Enter your move \"x y\": " << endl;
  while (read) {
    int i = 0;
    bool valid_token = true;
    getline(cin, move);

    char* copy_move = strdup(move.c_str());
    token = strtok(copy_move, " ");
    while (token != NULL) {
      if (atoi(token) < 0 || atoi(token) > 7) {
        cout << "Invalide position 0 <= index < 8" << endl;
        valid_token = false;
        break;
      }
      if (i > 1) {
        cout << "Invalide number of argument" << endl;
        valid_token = false;
        break;
      }
      coordinate[i] = atoi(token);
      token = strtok(NULL, " ");
      i++;
    }
    if (valid_token) {
      if ((i - 1) != 1) {
        cout << "Invalide number of argument" << endl;
        continue;
      }
      read = false;
    }
  }

  for (auto it = coordinate.begin(); it != coordinate.end(); ++it) {
    cout << *it << endl;
  }

  return coordinate;
}
