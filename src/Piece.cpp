#include "Piece.hpp"

/* -------------------------------------------- */
/*                     Piece                    */
/* -------------------------------------------- */
Piece::Piece(int x, int y, bool color) : x_(x), y_(y), color_(color) {}

void Piece::move(int x, int y) {}

/* -------------------------------------------- */
/*                     King                     */
/* -------------------------------------------- */
King::King(int x, int y, bool color) : Piece(x, y, color) {}
void King::validate_move(int x, int y) {}

/* -------------------------------------------- */
/*                     Queen                    */
/* -------------------------------------------- */
Queen::Queen(int x, int y, bool color) : Piece(x, y, color) {}
void Queen::validate_move(int x, int y) {}

/* -------------------------------------------- */
/*                     Rook                     */
/* -------------------------------------------- */
Rook::Rook(int x, int y, bool color) : Piece(x, y, color) {}
void Rook::validate_move(int x, int y) {}

/* -------------------------------------------- */
/*                    Knight                    */
/* -------------------------------------------- */
Knight::Knight(int x, int y, bool color) : Piece(x, y, color) {}
void Knight::validate_move(int x, int y) {}

/* -------------------------------------------- */
/*                    Bishop                    */
/* -------------------------------------------- */
Bishop::Bishop(int x, int y, bool color) : Piece(x, y, color) {}
void Bishop::validate_move(int x, int y) {}

/* -------------------------------------------- */
/*                     Pawn                     */
/* -------------------------------------------- */
Pawn::Pawn(int x, int y, bool color, bool can_move)
    : Piece(x, y, color), can_move_(can_move) {}

void Pawn::validate_move(int x, int y) {}

void Pawn::forward() {}

void Pawn::promote() {}
