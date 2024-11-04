#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QObject>
#include <QVariantList>

using possibleMoves = std::vector<std::vector<int>>;

class ChessPiece
{
protected:
    using piecesVector = std::vector<std::unique_ptr<ChessPiece>>;

public:
    ChessPiece(int posX, int posY, bool isWhite);
    QVariantList getPieceData();
    virtual possibleMoves getPossibleMoves(piecesVector const &pieces);

protected:
    QString name;
    int posX;
    int posY;
    bool isWhite;
};

#endif // CHESSPIECE_H
