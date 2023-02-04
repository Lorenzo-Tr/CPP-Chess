#pragma once
#include <array>
#include <string>
#include "E_Color.hpp"
#include "Piece.hpp"

using namespace std;

class Utils {
 public:
  Utils() = delete;
  Utils(const Utils&) = delete;
  Utils& operator=(const Utils&) = delete;
  ~Utils() = delete;

  static void parse_fen(const string& fen_code,
                        array<Piece*, 64>& board,
                        E_Color& color,
                        array<bool, 4>& castle_rights,
                        array<int, 2>& en_passant);
  static void clear();
  static bool isUnderAttack(int x,
                            int y,
                            E_Color color,
                            const array<Piece*, 64>& board);

 private:
  static Piece* char_to_piece(int index, char letter);
  static string::const_iterator parse_board(string::const_iterator it,
                                            string::const_iterator end,
                                            array<Piece*, 64>& board);
  static string::const_iterator parse_turn(string::const_iterator it,
                                           E_Color& turn);
  static string::const_iterator parse_castle_rights(
      string::const_iterator it,
      string::const_iterator end,
      array<bool, 4>& castle_rights);
  static string::const_iterator parse_en_passant(string::const_iterator it,
                                                 array<int, 2>& en_passant);

  static bool isUnderAttackDiagonal(int x,
                                    int y,
                                    E_Color color,
                                    const array<Piece*, 64>& board);
  static bool isUnderAttackHorizontalOrVertical(int x,
                                                int y,
                                                E_Color color,
                                                const array<Piece*, 64>& board);
  static bool isUnderAttackByKnight(int x,
                                    int y,
                                    E_Color color,
                                    const array<Piece*, 64>& board);
  static bool isUnderAttackByPawn(int x,
                                  int y,
                                  E_Color color,
                                  const array<Piece*, 64>& board);
};