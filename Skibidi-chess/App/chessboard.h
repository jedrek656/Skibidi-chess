#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVariantList>
#include <QAbstractListModel>
#include <iostream>

#include "chesspiece.h"
#include "spelllist.h"

class ChessBoard : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        PosXRole,
        PosYRole,
        IsWhiteRole,
    };

    enum Spells {
        HawkTuah = 0,
        Asbestos,
        CheeseDrippy,
    };

    explicit ChessBoard(QObject *parent = nullptr);

    /* REQUIRED METHODS FOR QABSTRACT LIST */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &idx, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    /**/

    void setSpellList(SpellList* spellist);
    SpellList *getSpellList() const;
    friend std::ostream &operator<<(std::ostream &out, const ChessBoard &board);
    friend std::istream &operator>>(std::istream &in, ChessBoard &board);

    void clearList();

public slots:
    std::vector<std::vector<int>> getPossibleMoves(int index);
    void movePiece(int idx, int newPosX, int newPosY);
    void capturePiece(int idx, int newPosX, int newPosY);
    void enPassant(int idx, int newPosX, int newPosY);
    void promotePiece(int idx, QString name);
    void castling(int idx, int newPosX, int newPosY);
    void loadPosition(QString position = "default");

    int getActivePiece() const;
    void setActivePiece(int newActivePiece);

    void getPossibleSpellFields(int spellIdx, bool isWhite);
    void resetPossibleSpellFields();

signals:
    void changePlayer();
    void chessboardLoaded();
    void activePieceChanged();
    void gameEnd(QString message);
    void promotionDialog(int idx, bool isWhite);

    void spellFieldsGenerated(std::vector<std::vector<int>> fields);

private:

    int activePiece = -1;
    int enPassantX = -1;
    std::vector <std::unique_ptr<ChessPiece>> pieces;
    void removeItem(int idx);
    SpellList *spellList;

    template <typename T>
    void addItem(int posX, int posY, bool isWhite);
    void loadDefaultPosition();

};

#endif // CHESSBOARD_H
