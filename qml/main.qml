import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
	id:root
	visible: true
	width: Qt.platform.os === "android"? Screen.width: 800
	height: Qt.platform.os === "android"? Screen.height: 600


	// *** Game View ***
	GameView {
		id:gameView
		// Gameview is disabled when gameViewHider is shown
		enabled: gameViewHider.state == "hide"
	}
	// *** Game View Hider ***
	Rectangle {
		id:gameViewHider
		anchors.fill: parent
		color:"black"
		opacity: 0.7
		states: [
			State{
				name:"hide"
				when: menuPanel.state == "hide"
				PropertyChanges {
					target: gameViewHider
					opacity: 0.0
				}
			}
		]
		transitions: Transition {
			NumberAnimation {
				properties:"opacity"
				duration: 400
			}
		}
	}
	ResultPanel {
		id:resultPanel
	}
	// *** Main Menu panel ***
	MenuPanel {
		id: menuPanel
	}

}
