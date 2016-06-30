import QtQuick 2.0
import Game 1.0
Rectangle {
	id:resultPanel
	x:0;
	y:0
	width:parent.width
	height:parent.height
	color:"red"
//	opacity:  game.state == Game.PLAYING || game.state == Game.READY
	Item {
		id:minimizeButton
		width:80
		height:80
		anchors.top: parent.top
		anchors.left: parent.left
		Image {
			source: "qrc:/Images/Images/minimize.png"
			anchors.centerIn: parent
		}
		MouseArea {
			anchors.fill: parent
			onClicked: {
				mainWidget.showMinimized()
			}
		}
	}
	Item {
		id:closeButton
		width:80
		height:80
		anchors.top: parent.top
		anchors.right: parent.right
		Image {
			source: "qrc:/Images/Images/close.png"
			anchors.centerIn: parent
		}
		MouseArea {
			anchors.fill: parent
			onClicked: {
				mainWidget.close()
			}
		}
	}
	Frame {
		id:boxWin
		width:300
		height:200
		anchors.centerIn: parent
		Text {
			id: textWin
			anchors.horizontalCenter: parent.horizontalCenter
			font.family: "Helvetica"
			font.pointSize: 28
			smooth:true
			color:"gray"
			style: Text.Outline
			styleColor:"black"
			text: "YOU WIN!"
		}
		Button {
			width:120
			anchors.top: textWin.bottom
			anchors.topMargin: 20
			anchors.horizontalCenter: parent.horizontalCenter
			text:"Next"
			onClicked: {
				game.startGame()
			}
		}
	}
	Frame {
		id:boxLose
		width:300
		height:200
		anchors.centerIn: parent
		Text {
			id: textLose
			anchors.horizontalCenter: parent.horizontalCenter
			font.family: "Helvetica"
			font.pointSize: 28
			smooth:true
			color:"gray"
			style: Text.Outline
			styleColor:"black"
			text: "GAME OVER!"
		}
		Button {
			width:120
			anchors.top: textLose.bottom
			anchors.topMargin: 20
			anchors.horizontalCenter: parent.horizontalCenter
			text:"Restart"
			onClicked: {
				game.reStart()
			}
		}
	}
	Rectangle {
		id:gameResultHider
		anchors.fill: parent
		color:"black"
		opacity: 0.7
		states: [
			State{
				name:"hide"
				when: resultPanel.state == "hide"
				PropertyChanges {
					target: gameResultHider
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

	states: [
		State {
			name:"hide"
			when: game.state == Game.READY || Game.state == Game.PLAYING
			PropertyChanges {
				target: resultPanel
				opacity:0
				y: -resultPanel.height
			}
		}
	]
	transitions: Transition {
		NumberAnimation {
			properties: "opacity, y"
			duration:400
		}
	}
}
