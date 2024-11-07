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
    QVariantList getPieceData() const;
    void moveTo(int newPosX, int newPosY);
    virtual possibleMoves getPossibleMoves(piecesVector const &pieces) const;
    int getPosX() const;
    int getPosY() const;

protected:
    QString name;
    int posX;
    int posY;
    bool isWhite;
};

#endif // CHESSPIECE_H
