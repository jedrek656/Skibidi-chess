#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QString>
#include <QVariantList>
#include <iostream>

using possibleMoves = std::vector<std::vector<int>>;

class ChessPiece
{


public:

    using piecesVector = std::vector<std::unique_ptr<ChessPiece>>;
    enum moveType{
        move = 0,
        capture = 1,
        enpassan = 2,
        castling = 3
    };

    ChessPiece(int posX, int posY, bool isWhite);
    virtual QVariantList getPieceData() const;
    virtual void moveTo(int newPosX, int newPosY);
    virtual possibleMoves getPossibleMoves(piecesVector const &pieces, int enPassantX) const;
    QString getName() const;
    int getPosX() const;
    int getPosY() const;

    bool getIsWhite() const;

    operator QString() const;
    friend std::ostream &operator<<(std::ostream &out, const ChessPiece &piece);
    friend std::istream &operator>>(std::istream &in, ChessPiece &piece);

protected:
    QString name;
    int posX;
    int posY;
    bool isWhite;
};

#endif // CHESSPIECE_H
