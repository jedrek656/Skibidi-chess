#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVariantList>

#include "chesspiece.h"

class ChessBoard : public QObject
{
    Q_OBJECT
public:
    explicit ChessBoard(QObject *parent = nullptr, QString position = "default");

public slots:
    int getNumOfPieces();
    QVariantList getPiece(int index);
    std::vector<std::vector<int>> getPossibleMoves(int index);
    void movePiece(int pieceIdx, int newPosX, int newPosY);
    void capturePiece(int pieceIdx, int newPosX, int newPosY);

signals:

private:
    std::vector <std::unique_ptr<ChessPiece>> pieces;
    void loadDefaultPosition();
};

#endif // CHESSBOARD_H
