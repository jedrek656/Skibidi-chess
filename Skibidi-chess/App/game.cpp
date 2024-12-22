#include "game.h"
#include <QCoreApplication>
#include <QDebug>

#include <QGuiApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QDir>
#include <QFile>

Game::Game(QObject *parent, ChessBoard *chessboard)
    : QObject{parent}
{
    this->chessboard = chessboard;
    this->player1 = std::make_unique<Player>(Player{true});
    this->player2 = std::make_unique<Player>(Player(false));
    this->turn = true;
}

void Game::closeApp() const {
    QCoreApplication::quit();
}

void Game::setChessboard(ChessBoard *chessboard){
    this->chessboard = chessboard;
}

void Game::changeTurn() {
    this->turn = !this->turn;
}

void Game::pauseGame()
{
    emit gamePaused();
}

bool Game::checkTurn() {
    return this->turn;
}

void Game::saveFile(QString path)
{
    std::ofstream file;
    file.open(path.toStdString(), std::ofstream::out | std::ofstream::trunc);
    Q_ASSERT(file.is_open());
    //file << *this;
    file << *this->chessboard;
    file.close();
}

void Game::loadFile(QString path)
{
    std::ifstream file;
    file.open(path.toStdString(), std::ofstream::in);
    Q_ASSERT(file.is_open());
    chessboard->clearList();

    file >> *this->chessboard;
    file.close();
    emit chessboard->chessboardLoaded();
}

void Game::openSaveDialog() {
    QString folderPath = QFileDialog::getSaveFileName(nullptr, "Select Folder to Save File", QDir::homePath(), "Skibi Files (*.skibi)");
    if (folderPath.isEmpty()) {
        qDebug() << "No folder selected.";
        return;
    }
    saveFile(folderPath);
}

void Game::openLoadDialog() {
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Folder to Save File", QDir::homePath(), "Skibi Files (*.skibi)");
    if (filePath.isEmpty()) {
        qDebug() << "No file selected.";
        return;
    }
    loadFile(filePath);
}

/*Player Game::getCurrentPlayer() {
    if (this->turn == true)
        return this->player1;
    else
        return this->player2;
}*/
