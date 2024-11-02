#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "chessboard.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr, ChessBoard *chessboard = nullptr);
    void setChessboard(ChessBoard *chessboard);

public slots:
    void closeApp() const;

signals:

private:
    ChessBoard *chessboard;
};

#endif // GAME_H
