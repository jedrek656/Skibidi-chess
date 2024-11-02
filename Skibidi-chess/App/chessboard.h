#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include "chesspiece.h"

class ChessBoard : public QObject
{
    Q_OBJECT
public:
    explicit ChessBoard(QObject *parent = nullptr);

public slots:

signals:

private:
    QVector<ChessPiece> pieces;
};

#endif // CHESSBOARD_H
