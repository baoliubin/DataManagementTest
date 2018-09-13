#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>

#include "mystringobject.h"

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MyStringObject myStringObject;
    engine.rootContext()->setContextProperty("myStringObject",&myStringObject);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
