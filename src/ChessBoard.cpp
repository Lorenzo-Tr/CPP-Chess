#include "ChessBoard.hpp"
#include <iostream>
#include <typeinfo>
#include "Game.hpp"
#include "Piece.hpp"
#include "Utils.hpp"
#include "cstdlib"

using namespace std;

ChessBoard::ChessBoard()
    : board_(),
      castle_rights_(),
      en_passant_(),
      NumSquaresToEdge(nullptr),
      historical_(60) {
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

void ChessBoard::save_move(Move* m, Piece* c, Piece* p) {
  historical_.push_back(new Historical(m, c, p));
}

bool ChessBoard::check_move(int x1, int y1, int x2, int y2) {
  if (x2 > 7 || x2 < 0 || y2 > 7 || y2 < 0) {
    return false;
  }

  if (x1 == x2 && y1 == y2) {
    return false;
  }

  int TargetIndex = y2 * 8 + x2;

  for (auto it : legalMoves) {
    if (TargetIndex == it->TargetSquare) {
      return true;
    }
  }

  return false;
}

bool ChessBoard::play_move(int x1, int y1, int x2, int y2) {
  Piece* captured = nullptr;
  Piece* promoted = nullptr;

  if (check_move(x1, y1, x2, y2)) {
    board_[y1 * 8 + x1]->move(x2, y2);
    captured = board_[y2 * 8 + x2];

    board_[y2 * 8 + x2] = board_[y1 * 8 + x1];
    if (board_[y1 * 8 + x1]->getType() == "pawn") {
      Pawn* pawn = dynamic_cast<Pawn*>(board_[y1 * 8 + x1]);
      // Call promote function
      Piece* promoted_piece = pawn->promote();
      if (promoted_piece != nullptr) {
        promoted = board_[y1 * 8 + x1];
        // Replace the pawn with the promoted piece
        board_[y2 * 8 + x2] = promoted_piece;
        // Delete the pawn
        delete pawn;
      }
    }
    save_move(new Move((y1 * 8 + x1), (y2 * 8 + x2)), captured, promoted);
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
      Piece* piece = board_[i * 8 + j];
      if (piece) {
        if (check_move(x, y, j, i)) {
          cout << "#" << *piece;
        } else {
          cout << *piece << " ";
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
      }

      piece->getPseudoLegalMoves().push_back(new Move(start, targetSquare));

      // Need to capture the opponent's piece before going further
      if (pieceOnTargetSquare) {
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

    if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
      continue;
    }

    int targetSquare = ny * 8 + nx;
    if (board_[targetSquare]) {
      if (board_[targetSquare]->getColor() == piece->getColor()) {
        continue;
      }
    }

    piece->getPseudoLegalMoves().push_back(new Move(start, targetSquare));
  }
}

void ChessBoard::generatePawnMoves(int start, Piece* piece) {
  int dx[] = {0, 0, -1, 1};
  int dy[] = {2, 1, 1, 1};
  int dir = piece->getColor() == E_Color::WHITE ? -1 : 1;
  Pawn* pawn = dynamic_cast<Pawn*>(piece);

  for (int i = 0; i < 4; i++) {
    int nx = (start % 8) + dx[i];
    int ny = (start / 8) + (dy[i] * dir);

    if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
      continue;
    }

    int targetSquare = ny * 8 + nx;
    if (i == 0 && pawn->isAlreadyMove()) {
      continue;
    }

    if (i >= 2) {
      if (board_[targetSquare]) {
        if (board_[targetSquare]->getColor() == piece->getColor()) {
          continue;
        } else {
          piece->getPseudoLegalMoves().push_back(new Move(start, targetSquare));
          continue;
        }
      }
    } else {
      piece->getPseudoLegalMoves().push_back(new Move(start, targetSquare));
    }
  }
}

void ChessBoard::generateKingMoves(int start, Piece* piece) {
  int dx[] = {1, -1, -1, 1, 1, 0, -1, 0};
  int dy[] = {1, -1, 1, -1, 0, 1, 0, -1};

  for (int i = 0; i < 4; i++) {
    int nx = (start % 8) + dx[i];
    int ny = (start / 8) + dy[i];

    if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) {
      continue;
    }

    int targetSquare = ny * 8 + nx;
    if (board_[targetSquare]) {
      if (board_[targetSquare]->getColor() == piece->getColor()) {
        continue;
      }
    }

    piece->getPseudoLegalMoves().push_back(new Move(start, targetSquare));
  }
}

void ChessBoard::generateMoves(E_Color ColourToMove) {
  for (int S_start = 0; S_start < 64; S_start++) {
    Piece* piece = board_[S_start];
    if (piece) {
      vector<Move*>& pseudoLegalMoves = piece->getPseudoLegalMoves();
      if (pseudoLegalMoves.size() > 0) {
        pseudoLegalMoves.erase(pseudoLegalMoves.begin(),
                               pseudoLegalMoves.end());
      }
      if (piece->getColor() == ColourToMove) {
        if (Utils::IsSlidingPiece(piece)) {
          generateSlidingMoves(S_start, piece);
        }
        if (piece->getType() == "knight") {
          generateKnightMoves(S_start, piece);
        }
        if (piece->getType() == "pawn") {
          generatePawnMoves(S_start, piece);
        }
        if (piece->getType() == "King") {
          generateKingMoves(S_start, piece);
        }
      }
    }
  }
}

void ChessBoard::cancel_move() {
  if (historical_.size() > 0) {
    Historical* last = historical_.back();
    Move* lastMove = last->getMove();
    Piece* capturedPiece = last->getCapturedPiece();
    board_[lastMove->StartSquare] = board_[lastMove->TargetSquare];
    if (capturedPiece) {
      board_[lastMove->TargetSquare] = capturedPiece;
    } else {
      board_[lastMove->TargetSquare] = nullptr;
    }
  }
  historical_.pop_back();
}

void ChessBoard::generateLegalMoves(E_Color ColourToMove) {
  E_Color opponentColor = ColourToMove == WHITE ? BLACK : WHITE;
  int kingSquare;
  for (int i = 0; i < 64; i++) {
    Piece* piece = board_[i];
    if (piece && piece->getColor() == ColourToMove) {
      vector<Move*> pseudoLegalMoves = piece->getPseudoLegalMoves();
      if (piece->getType() == "king") {
        kingSquare = i;
      }
      for (Move* moveToVerify : pseudoLegalMoves) {
        int x1 = moveToVerify->StartSquare % 8;
        int y1 = moveToVerify->StartSquare / 8;
        int x2 = moveToVerify->TargetSquare % 8;
        int y2 = moveToVerify->TargetSquare / 8;
        play_move(x1, y1, x2, y2);
        generateMoves(opponentColor);
        for (int j = 0; j < 64; j++) {
          Piece* opponentPiece = board_[j];
          if (opponentPiece) {
            vector<Move*> opponentPseudoLegalMoves =
                opponentPiece->getPseudoLegalMoves();
            for (Move* response : opponentPseudoLegalMoves) {
              if (response->TargetSquare == kingSquare) {
              } else {
                getLegalMoves().push_back(moveToVerify);
              }
            }
          }
        }
        cancel_move();
      }
    }
  }
}