#include "Game.hpp"
#include <iostream>
#include "E_Color.hpp"
#include "Utils.hpp"

using namespace std;

Game::Game(const string& fen) : chessboard_(), actual_player_() {
  players_ = {new Player(chessboard_, "white", E_Color::WHITE),
              new Player(chessboard_, "black", E_Color::BLACK)};

  array<Piece*, 64>& board = chessboard_.getBoard();
  E_Color actual_player;
  array<bool, 4>& castle_rights = chessboard_.getCastle_rights();
  array<int, 2>& en_passant = chessboard_.getEnPassant();

  Utils::parse_fen(fen, board, actual_player, castle_rights, en_passant);

  actual_player_ = players_[actual_player];
}

void Game::change_player() {
  E_Color turn = actual_player_->getColor() == WHITE ? BLACK : WHITE;
  actual_player_ = players_[turn];
}

bool Game::check_echec() {
  int kingX, kingY;
  E_Color kingColor = actual_player_->getColor();
  array<Piece*, 64>& board = chessboard_.getBoard();

  for (int i = 0; i < 64; i++) {
    int x = i % 8;
    int y = i / 8;
    Piece* piece = board[y * 8 + x];
    if (piece && piece->getColor() == kingColor) {
      kingX = x;
      kingY = y;
    }
  }

  (void)kingX;
  (void)kingY;

  // return Utils::isUnderAttack(kingX, kingY, kingColor, , board);
  return false;
}

bool Game::check_mat() {
  int kingX, kingY;
  E_Color kingColor = actual_player_->getColor();
  array<Piece*, 64>& board = chessboard_.getBoard();

  for (int i = 0; i < 64; i++) {
    int x = i % 8;
    int y = i / 8;
    Piece* piece = board[y * 8 + x];
    if (piece && piece->getColor() == kingColor) {
      kingX = x;
      kingY = y;
    }
  }

  (void)kingX;
  (void)kingY;

  if (check_echec()) {
    return true;
  }

  return false;
}

void Game::cancel_move() {
  auto board = chessboard_.getBoard();
  if (chessboard_.GetHistorical().size() > 0) {
    Historical* last = chessboard_.GetHistorical().back();
    Move* lastMove = last->getMove();
    Piece* capturedPiece = last->getCapturedPiece();
    board[lastMove->StartSquare] = board[lastMove->TargetSquare];
    if (capturedPiece) {
      board[lastMove->TargetSquare] = capturedPiece;
    } else {
      board[lastMove->TargetSquare] = nullptr;
    }
  }
  chessboard_.GetHistorical().pop_back();
}

void Game::generateLegalMoves(E_Color ColourToMove) {
  auto board_ = chessboard_.getBoard();
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
        actual_player_->play_move(x1, y1, x2, y2);
        change_player();
        chessboard_.generateMoves(GetActualPlayer()->getColor());
        for (int j = 0; j < 64; j++) {
          Piece* opponentPiece = board_[j];
          if (opponentPiece) {
            vector<Move*> opponentPseudoLegalMoves =
                opponentPiece->getPseudoLegalMoves();
            for (Move* response : opponentPseudoLegalMoves) {
              if (response->TargetSquare == kingSquare) {
              } else {
                chessboard_.getLegalMoves().push_back(moveToVerify);
              }
            }
          }
        }
        cancel_move();
      }
    }
  }
}
