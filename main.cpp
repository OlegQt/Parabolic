#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cdraw.h>
#include <QQuickStyle>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::addLibraryPath("D:/QTLib/5.14.0/mingw73_64/plugins");//добавили статическое распложение патча
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");//Для использования тем материалов надо добавить quickcontrols2 в qmake
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    //Регистрируем наш класс как элемент QML
    qmlRegisterType<CDraw>("drawingTarget",1,0,"Target");
    engine.load(url);


    return app.exec();
}
