#ifndef SPELLLIST_H
#define SPELLLIST_H

#include <QObject>
#include <QAbstractListModel>
#include "spell.h"

class Game;

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
    };
    explicit SpellList(QObject *parent = nullptr);

    /* REQUIRED METHODS FOR QABSTRACT LIST */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &idx, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    /**/

    void setGame(Game *newGame);

public slots:
    void updateLifespans();
    void setActiveSpell(int newActiveSpell);
    int getActiveSpell() const;

    void castSpell(int posX, int posY);
    std::vector <std::unique_ptr<Spell>> *getSpells();

signals:
    void activeSpellChanged(int index);
    void hideSpells();

private:
    std::vector <std::unique_ptr<Spell>> spells;

    vecIterator removeItem(vecIterator currIterator);
    void clearList();

    int activeSpell = -1;

    template <typename T>
    void addItem(int posX, int posY);

    Game* game;
};

#endif // SPELLLIST_H
