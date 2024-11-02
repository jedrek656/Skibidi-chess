#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>

class MainMenu : public QObject
{
    Q_OBJECT
public:
    explicit MainMenu(QObject *parent = nullptr);

public slots:
    void exit();

signals:
    void closeApp();
};

#endif // MAINMENU_H
