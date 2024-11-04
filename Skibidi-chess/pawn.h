#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces) override;
};

#endif // PAWN_H
