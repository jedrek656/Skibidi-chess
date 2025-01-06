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

ChessBoard *Game::getChessboard() const
{
    return this->chessboard;
}

void Game::decreaseCurrPlayerMana(int cost)
{
    if (this->checkTurn()){
        player1->subtractMana(cost);
        return;
    }
    player2->subtractMana(cost);
}

void Game::changeTurn() {
    if (turn){
        player1->addMana();
    }
    else{
        player2->addMana();
    }
    this->turn = !this->turn;
    emit updateMana();
}

void Game::pauseGame()
{
    emit gamePaused();
}

void Game::openSettings() {
    emit menuPaused();
}

bool Game::checkTurn() {
    return this->turn;
}

void Game::saveFile(QString path)
{
    std::ofstream file;
    file.open(path.toStdString(), std::ofstream::out | std::ofstream::trunc);
    Q_ASSERT(file.is_open());
    file << this->turn << "\n";
    file << this->player1->getMana() << "\n";
    file << this->player2->getMana() << "\n";
    file << this->chessboard->getSpellList()->getSpells()->size() << "\n";
    for (auto& spell: *this->chessboard->getSpellList()->getSpells()){
        for(int i=0; i<4; ++i)
        {
            file << spell->getSpell()[i].toString().toStdString() << "\n";
        }
    }
    file << *this->chessboard;
    file.close();
}

void Game::loadFile(QString path)
{
    std::ifstream file;
    file.open(path.toStdString(), std::ofstream::in);
    Q_ASSERT(file.is_open());
    chessboard->clearList();
    int mana, spells;
    file >> this->turn;
    file >> mana;
    this->player1->assignMana(mana);
    file >> mana;
    this->player2->assignMana(mana);
    file >> spells;
    for (int i=0; i<spells; ++i){
        std::string name;
        int posX, posY, lifespan;
        std::getline(file, name);
        std::getline(file, name);
        file >> posX >> posY >> lifespan;
        this->chessboard->getSpellList()->addSpellDirectly(QString::fromStdString(name), posX, posY, lifespan);
    }
    file >> *this->chessboard;
    file.close();
    emit chessboard->chessboardLoaded();
    emit updateMana();
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

int Game::getMana(bool player) const
{
    if(player) return player1->getMana();
    return player2->getMana();
}

int Game::getCurrPlayerMana() const
{
    return getMana(this->turn);
}
