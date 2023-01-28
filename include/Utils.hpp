#pragma once
#include <string>
#include "E_Color.hpp"

using namespace std;

class Utils {
 public:
  Utils() = delete;
  Utils(const Utils&) = delete;
  Utils& operator=(const Utils&) = delete;
  ~Utils() = delete;

  static void parse_fen(const string& fen_code,
                        int* board,
                        E_Color* color,
                        bool* castle_rights);
  static char int_to_char_piece(int value);
  static int char_to_int_piece(char letter);
  static void move_iterator(string::const_iterator it);
  static string::const_iterator parse_board(string::const_iterator it,
                                            string::const_iterator end,
                                            int* board);
  static string::const_iterator parse_turn(string::const_iterator it,
                                           E_Color* turn);
  static string::const_iterator parse_castle_rights(string::const_iterator it,
                                                    string::const_iterator end,
                                                    bool* castle_rights);
};