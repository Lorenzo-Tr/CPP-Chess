#include "Historical.hpp"

Historical::Historical(Move* m, Piece* c, Piece* p)
    : move_(m), captured_piece_(c), promoted_piece_(p) {}