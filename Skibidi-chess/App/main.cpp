#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "autogen/environment.h"

#include "game.h"
#include "chessboard.h"
#include "spelllist.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QApplication app(argc, argv);

    Game game;
    ChessBoard chessboard(&game);
    SpellList spellList(&chessboard);

    game.setChessboard(&chessboard);
    chessboard.setSpellList(&spellList);
    spellList.setGame(&game);

    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    //MAKING CLASSES VISIBLE IN QML

    engine.rootContext()->setContextProperty("GameObj", &game);
    engine.rootContext()->setContextProperty("ChessboardObj", &chessboard);
    engine.rootContext()->setContextProperty("SpellListObj", &spellList);



    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
