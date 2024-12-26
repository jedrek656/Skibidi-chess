#ifndef DUMMYPIECE_H
#define DUMMYPIECE_H

#include "chesspiece.h"

class DummyPiece : public ChessPiece
{
public:
    DummyPiece(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces, int enPassantX) const override;
};

#endif // DUMMYPIECE_H
