#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces) const override;
};

#endif // KNIGHT_H