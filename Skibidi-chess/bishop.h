#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(int posX, int posY, bool isWhite);
    static possibleMoves checkDiagonal(int x, int y, bool is_white, std::vector<std::unique_ptr<ChessPiece>> const &pieces);
    possibleMoves getPossibleMoves(piecesVector const &pieces) const override;
};

#endif // BISHOP_H
