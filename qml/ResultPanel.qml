import QtQuick 2.0
import Game 1.0
Rectangle {
	id:resultPanel
	x:0;
	y:0
	width:parent.width
	height:parent.height
	color:"gray"
	opacity:  0
	Frame {
		id:boxWin
		width:300
		height:200
		anchors.centerIn: parent
		opacity: resultPanel.state != "Lose"
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
			anchors.topMargin: 50
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
		opacity: resultPanel.state != "Win"
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
			anchors.topMargin: 50
			anchors.horizontalCenter: parent.horizontalCenter
			text:"Restart"
			onClicked: {
				game.reStart()
			}
		}
	}
//	Rectangle {
//		id:gameResultHider
//		anchors.fill: parent
//		color:"black"
//		opacity: 0.7
//		states: [
//			State{
//				name:"hide"
//				when: resultPanel.state == "hide"
//				PropertyChanges {
//					target: gameResultHider
//					opacity: 0.0
//				}
//			}
//		]
//		transitions: Transition {
//			NumberAnimation {
//				properties:"opacity"
//				duration: 400
//			}
//		}
//	}

	states: [
		State {
			name:"Hide"
			when: game.state == Game.READY || game.state == Game.PLAYING
			PropertyChanges {
				target: resultPanel
				opacity:0
				y: -resultPanel.height
			}
		},
		State {
			name:"Lose"
			when: game.state == Game.LOSE
			PropertyChanges {
				target: resultPanel
				opacity: 0.7
				y:0
			}
		},
		State {
			name:"Win"
			when: game.state == Game.WIN
			PropertyChanges {
				target: resultPanel
				opacity: 0.7
				y:0
			}
		}

	]
	transitions: Transition {
		NumberAnimation {
			properties: "opacity, y"
			duration:1000
		}
	}
}
