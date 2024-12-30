#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <iostream>
#include <fstream>
#include "chessboard.h"
#include "player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr, ChessBoard *chessboard = nullptr);
    void setChessboard(ChessBoard *chessboard);

    void decreaseCurrPlayerMana(int cost);

public slots:
    void closeApp() const;
    bool checkTurn();
    void changeTurn();
    void pauseGame();
    void openSettings();


    void openSaveDialog();
    void openLoadDialog();

    int getMana(bool player) const;
    int getCurrPlayerMana() const;

signals:
    void gamePaused();
    void menuPaused();
    void updateMana();

private:
    ChessBoard *chessboard;
    std::unique_ptr<Player> player1, player2;
    bool turn = true;  // true - player 1, false = player2

    void saveFile(QString path);
    void loadFile(QString path);
};

#endif // GAME_H
