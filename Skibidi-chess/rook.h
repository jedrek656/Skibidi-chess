#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(int posX, int posY, bool isWhite);
    static possibleMoves checkHorizontal(int x, int y, bool is_white, std::vector<std::unique_ptr<ChessPiece>> const &pieces);
    possibleMoves getPossibleMoves(piecesVector const &pieces) const override;
};

#endif // ROOK_H
