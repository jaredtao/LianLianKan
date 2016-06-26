#include <QGuiApplication>
#include <QtQml>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include "music.h"
#include "game.h"
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);


	Game game;
	Music music;

	QQuickView view;

	view.rootContext()->setContextProperty("mainWidget", &view);
	view.rootContext()->setContextProperty("game", &game);
	view.rootContext()->setContextProperty("music", &music);

	view.setSource(QUrl("qrc:/main.qml"));
	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setMaximumSize(QSize(800, 600));
	view.setMinimumSize(QSize(400, 300));
	view.show();
	return app.exec();

}
