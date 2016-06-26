import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
	visible: true
	width: 800
	height: 600

	GameView {
		id:gameView

	}

	MenuPanel {
		id: menuPanel
	}
}
