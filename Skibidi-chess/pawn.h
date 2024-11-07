#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces) const override;
    void moveTo(int newPosX, int newPosY) override;

private:
    bool isFirstMove = true;
};

#endif // PAWN_H
