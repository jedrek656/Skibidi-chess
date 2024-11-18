#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King : public ChessPiece
{
public:
    King(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces) const override;
};

#endif // KING_H