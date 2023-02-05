#include "ChessBoard.hpp"
#include <iostream>
#include <typeinfo>
#include "Game.hpp"
#include "Piece.hpp"
#include "Utils.hpp"
#include "cstdlib"

using namespace std;

ChessBoard::ChessBoard()
    : board_(), castle_rights_(), en_passant_(), NumSquaresToEdge(nullptr) {
  NumSquaresToEdge = new int*[64];

  for (size_t i = 0; i < 64; i++) {
    board_[i] = nullptr;
  }

  for (int i = 0; i < 4; i++) {
    castle_rights_[i] = false;
  }

  PrecomputedMoveDate();
}

ChessBoard::~ChessBoard() {
  for (int i = 0; i < 8; i++) {
    delete[] NumSquaresToEdge[i];
  }
  delete[] NumSquaresToEdge;
}

void ChessBoard::PrecomputedMoveDate() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int numNorth = 7 - i;
      int numSouth = i;
      int numWest = j;
      int numEast = 7 - j;

      int squareIndex = i * 8 + j;

      NumSquaresToEdge[squareIndex] = new int[8]{
          numNorth,
          numSouth,
          numWest,
          numEast,
          min(numNorth, numWest),
          min(numSouth, numEast),
          min(numNorth, numEast),
      };
    }
  }
}

bool ChessBoard::check_move(int x1, int y1, int x2, int y2) {
  if (x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) {
    return false;
  }

  if (x1 == x2 && y1 == y2) {
    return false;
  }

  // int kingX, kingY;
  // for (int i = 0; i < 64; i++) {
  //   int x = i % 8;
  //   int y = i / 8;
  //   Piece* piece = board_[y * 8 + x];
  //   if (piece && piece->getColor() == board_[y1 * 8 + x1]->getColor()) {
  //     kingX = x;
  //     kingY = y;
  //   }
  // }

  // (void)kingX;
  // (void)kingY;

  // if (Utils::isUnderAttack(kingX, kingY, board_[y1 * 8 + x1]->getColor(),
  //                     board_)) {
  //   return false;
  // }

  auto cur_piece = board_[y1 * 8 + x1];
  auto dest_piece = board_[y2 * 8 + x2];

  if (dest_piece != nullptr &&
      cur_piece->getColor() == dest_piece->getColor()) {
    return false;
  }

  if (board_[y1 * 8 + x1]->validate_move(x2, y2, board_)) {
    return true;
  }

  return false;
}

bool ChessBoard::play_move(int x1, int y1, int x2, int y2) {
  if (check_move(x1, y1, x2, y2)) {
    board_[y1 * 8 + x1]->move(x2, y2);
    board_[y2 * 8 + x2] = board_[y1 * 8 + x1];
    if (board_[y1 * 8 + x1]->getType() == "pawn") {
      Pawn* pawn = dynamic_cast<Pawn*>(board_[y1 * 8 + x1]);
      // Call promote function
      Piece* promoted_piece = pawn->promote();
      if (promoted_piece != nullptr) {
        // Replace the pawn with the promoted piece
        board_[y2 * 8 + x2] = promoted_piece;
        // Delete the pawn
        delete pawn;
      }
    }
    board_[y1 * 8 + x1] = nullptr;
    return true;
  } else {
    cout << "Invalid move !" << endl;
  }

  return false;
}

void ChessBoard::print() {
  cout << endl;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board_[i * 8 + j] != nullptr) {
        cout << *board_[i * 8 + j] << " ";
      } else {
        cout << ". ";
      }
    }
    cout << "  " << i << endl;
  }

  cout << endl;
  for (int j = 0; j < 8; j++) {
    cout << j << " ";
  }
  cout << endl;
}

void ChessBoard::print_playable_move(int x, int y) {
  cout << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int index = i * 8 + j;
      if (board_[index] != nullptr) {
        if (check_move(x, y, j, i)) {
          cout << "#" << *board_[index];
        } else {
          cout << *board_[index] << " ";
        }
      } else {
        if (check_move(x, y, j, i)) {
          cout << "# ";
        } else {
          cout << ". ";
        }
      }
    }
    cout << "  " << i << endl;
  }
  cout << endl;
  for (int j = 0; j < 8; j++) {
    cout << j << " ";
  }
  cout << endl;
}

void ChessBoard::generateSlidingMoves(int start, Piece* piece) {
  int startDireIndex = piece->getType() == "bishop" ? 4 : 0;
  int endDirIndex = piece->getType() == "rook" ? 4 : 8;

  for (int dir = startDireIndex; dir < endDirIndex; dir++) {
    for (int n = 0; n < NumSquaresToEdge[start][dir]; n++) {
      int targetSquare = start + DirectionOffsets[dir] * (n + 1);
      Piece* pieceOnTargetSquare = board_[targetSquare];
      // If pieceOnTarget is not null
      if (pieceOnTargetSquare) {
        // Blocked by friendly piece, so do not continue
        if (pieceOnTargetSquare->getColor() == piece->getColor()) {
          break;
        }

        piece->getLegalMoves().push_back(new Move(start, targetSquare));

        // Need to capture the opponent's piece before going further
        if (pieceOnTargetSquare->getColor() != piece->getColor()) {
          break;
        }
      }
    }
  }
}

void ChessBoard::generateKnightMoves(int start, Piece* piece) {
  int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
  int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

  for (int i = 0; i < 8; i++) {
    int nx = (start % 8) + dx[i];
    int ny = (start / 8) + dy[i];
    int targetSquare = ny * 8 + nx;
    if (board_[targetSquare]) {
      if (board_[targetSquare]->getColor() != piece->getColor()) {
        continue;
      }
      if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8) {
        piece->getLegalMoves().push_back(new Move(start, targetSquare));
      }
    }
  }
}

// void ChessBoard::generatePawnMoves(int start, Piece* piece) {}

// void ChessBoard::generateKingMoves(int start, Piece* piece) {}

void ChessBoard::generateMoves(E_Color ColourToMove) {
  for (int S_start = 0; S_start < 64; S_start++) {
    Piece* piece = board_[S_start];
    if (piece) {
      if (piece->getColor() == ColourToMove) {
        if (Utils::IsSlidingPiece(piece)) {
          generateSlidingMoves(S_start, piece);
        }
        if (piece->getType() == "knight") {
          generateKnightMoves(S_start, piece);
        }
      }
    }
  }
}