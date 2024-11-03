#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include "chesspiece.h"

using pieceInfo = std::tuple<QString, int, int, bool>;

class ChessBoard : public QObject
{
    Q_OBJECT
public:
    explicit ChessBoard(QObject *parent = nullptr, QString position = "default");

public slots:
    int getNumOfPieces();
    pieceInfo getPiece(int index);

signals:

private:
    QVector<std::unique_ptr<ChessPiece>> pieces;
    void loadDefaultPosition();
};

#endif // CHESSBOARD_H
