#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King : public ChessPiece
{
public:
    King(int posX, int posY, bool isWhite);
    possibleMoves getPossibleMoves(piecesVector const &pieces, int enPassantX) const override;
    void moveTo(int newPosX, int newPosY) override;

private:
    bool isFirstMove = true;
};

#endif // KING_H
