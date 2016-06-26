#include <QGuiApplication>
#include <QtQml>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include "audio.h"
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

//	QQmlApplicationEngine engine;
//	engine.load(QUrl(QLatin1String("qrc:/main.qml")));
//	Audio::init();
//	Audio::play("Sounds/backgrand.mp3");

	QQuickView view;

	view.setSource(QUrl("qrc:/main.qml"));
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setMaximumSize(QSize(800, 600));
	view.setMinimumSize(QSize(400, 300));
	view.show();
	return app.exec();

}
