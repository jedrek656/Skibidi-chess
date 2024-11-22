#ifndef SPELLLIST_H
#define SPELLLIST_H

#include <QObject>
#include <QAbstractListModel>
#include "spell.h"

using vecIterator = std::vector<std::unique_ptr<Spell>>::iterator;

class SpellList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        NameRole = Qt::UserRole + 1,
        PosXRole,
        PosYRole,
        LifespanRole,
        IsWhiteRole,
    };
    explicit SpellList(QObject *parent = nullptr);

    /* REQUIRED METHODS FOR QABSTRACT LIST */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &idx, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    /**/

public slots:
    void updateLifespans();


signals:

private:
    std::vector <std::unique_ptr<Spell>> spells;

    vecIterator removeItem(vecIterator currIterator);
    void clearList();

    template <typename T>
    void addItem(int posX, int posY, bool isWhite);
};

#endif // SPELLLIST_H