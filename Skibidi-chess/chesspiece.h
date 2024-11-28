#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QObject>
#include <QVariantList>

using possibleMoves = std::vector<std::vector<int>>;
enum moveType{
    move = 0,
    capture = 1,
    enpassan = 2,
    castling = 3,
    promotion = 4
};


class ChessPiece
{
protected:
    using piecesVector = std::vector<std::unique_ptr<ChessPiece>>;

public:
    ChessPiece(int posX, int posY, bool isWhite);
    virtual QVariantList getPieceData() const;
    virtual void moveTo(int newPosX, int newPosY);
    virtual possibleMoves getPossibleMoves(piecesVector const &pieces, int enPassantX) const;
    QString getName() const;
    int getPosX() const;
    int getPosY() const;

    bool getIsWhite() const;

    operator QString() const;

protected:
    QString name;
    int posX;
    int posY;
    bool isWhite;
};

#endif // CHESSPIECE_H
