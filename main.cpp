#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "audio.h"
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
	Audio::init();
	Audio::play("Sounds/backgrand.mp3");
	return app.exec();
}
