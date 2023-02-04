#include "Player.hpp"
#include <string.h>
#include <sstream>
#include <vector>
#include "Utils.hpp"

using namespace std;

Player::Player(ChessBoard& chessboard, string name, E_Color color)
    : chessboard_(chessboard), name_(name), color_(color) {}

int Player::play_move(int x1, int y1, int x2, int y2) {
  Utils::clear();
  chessboard_.play_move(x1, y1, x2, y2);

  return 0;
}

array<int, 4> Player::read_move() {
  string move;
  bool read = true;
  array<int, 4> coordinate;
  bool from = true;

  while (read) {
    const string& text = from ? " : Enter the piece you want to move \"x y\": "
                              : " : Enter where you want to move \"x y\": ";
    cout << endl << getColor() << text << endl;
    int i = from ? 0 : 2;

    getline(cin, move);
    istringstream iss(move);
    int x, y;
    if (!(iss >> x >> y) || x < 0 || x > 7 || y < 0 || y > 7) {
      cout << "Invalid position, the values should be between 0 and 7." << endl;
      continue;
    }
    auto selected_piece = chessboard_.getBoard()[y * 8 + x];
    if (from && selected_piece != nullptr &&
        selected_piece->getColor() != getColor()) {
      cout << "It's not your piece, play yours" << endl;
      continue;
    }

    coordinate[i] = x;
    coordinate[i + 1] = y;
    if (from) {
      chessboard_.print_playable_move(x, y);
      from = false;
      continue;
    }

    read = false;
  }

  return coordinate;
}
