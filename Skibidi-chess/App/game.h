#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "chessboard.h"
#include "player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr, ChessBoard *chessboard = nullptr);
    void setChessboard(ChessBoard *chessboard);
    // Player getCurrentPlayer();

public slots:
    void closeApp() const;
    bool checkTurn();
   void changeTurn();

signals:

private:
    ChessBoard *chessboard;
    std::unique_ptr<Player> player1, player2;
    bool turn = true;  // true - player 1, false = player2
};

#endif // GAME_H
