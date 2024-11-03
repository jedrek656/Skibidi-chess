#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#import <QObject>

using pieceInfo = std::tuple<QString, int, int, bool>;

class ChessPiece
{
public:
    ChessPiece(int posX, int posY, bool isWhite);
    pieceInfo getPieceDate();

private:
    QString name = "Piece";
    int posX;
    int posY;
    bool isWhite;
};

#endif // CHESSPIECE_H
