#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "autogen/environment.h"

int main(int argc, char *argv[])
{
    set_qt_environment();
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(mainQmlFile);
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");
    engine.load(url);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
