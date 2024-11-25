#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVariantList>
#include <QAbstractListModel>

#include "chesspiece.h"

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
    explicit ChessBoard(QObject *parent = nullptr);

    /* REQUIRED METHODS FOR QABSTRACT LIST */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &idx, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    /**/

public slots:
    std::vector<std::vector<int>> getPossibleMoves(int index) const;
    void movePiece(int idx, int newPosX, int newPosY);
    void capturePiece(int idx, int newPosX, int newPosY);
    void loadPosition(QString position = "default");

    int getActivePiece() const;
    void setActivePiece(int newActivePiece);

signals:
    void changePlayer();
    void chessboardLoaded();
    void activePieceChanged();
    void gameEnd(QString message);

private:

    int activePiece = -1;

    std::vector <std::unique_ptr<ChessPiece>> pieces;
    void removeItem(int idx);
    void clearList();

    template <typename T>
    void addItem(int posX, int posY, bool isWhite);
    void loadDefaultPosition();
};

#endif // CHESSBOARD_H
