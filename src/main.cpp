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

	qmlRegisterType<Tile>("GameCore", 1, 0, "Tile");
	qmlRegisterType<Game>("Game", 1, 0, "Game");
	view.rootContext()->setContextProperty("mainWidget", &view);
	view.rootContext()->setContextProperty("game", &game);
	view.rootContext()->setContextProperty("music", &music);

	view.setResizeMode(QQuickView::SizeRootObjectToView);
	view.setMaximumSize(QSize(800, 600));
	view.setMinimumSize(QSize(400, 300));

	view.setSource(QUrl("qrc:/qml/main.qml"));

	view.show();
	return app.exec();

}
