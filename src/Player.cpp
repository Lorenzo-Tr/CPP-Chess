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
  char* copy_move;
  char* token;
  array<int, 2> coordinate;
  int i = 0;

  cout << getColor() << " : Enter your move \"x y\": " << endl;
  getline(cin, move);
  // pos = move.find(split_char);
  // token = move.substr(0, pos);
  // move.erase(0, pos + 1);
  // coordinate[0] = atoi(token.c_str());
  // coordinate[1] = atoi(move.c_str());
  memcpy(copy_move, move.c_str(), move.size());
  token = strtok(copy_move, " ");
  while (token != NULL) {
    coordinate[i] = atoi(token);
    token = strtok(NULL, " ");
    i++;
  }
  // for ();
  // cout << move << endl;

  for (auto it = coordinate.begin(); it != coordinate.end(); ++it) {
    cout << *it << endl;
  }

  // Keep printing tokens while one of the
  // delimiters present in str[].
  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, "-");
  }

  // getline(cin, move, );

  // pch = strtok(move, " ");

  return coordinate;
}
