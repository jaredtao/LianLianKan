import QtQuick 2.0
import Game 1.0
Item {
	id: menuPanel
	width:parent.width
	height:parent.height
	property bool fluid3D: switch3D.on
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
		id:menuPanelFrame
		width:540
		height:500
		anchors.centerIn: parent

		Image{
			id:gameLogo
			anchors.top: parent.top
			anchors.topMargin: 10
			anchors.horizontalCenter: parent.horizontalCenter
			source:"qrc:/Images/Images/icon.png"
			Text {
				anchors.centerIn: parent
				font.family: "Helvetica"
				font.pointSize: 28
				smooth:true
				color:"white"
				style: Text.Outline
				styleColor: "black"
				text: "Lian-Lian-Kan"
			}
		}
		Row {
			anchors {
				left: parent.left;
				bottom: parent.bottom;
				right:parent.right;
				top:gameLogo.bottom;
				margins: 10
			}
			spacing: 10
			Frame {
				id: aboutArea
				width:300
				height:340
				gradient: Gradient {
					GradientStop { position: 0.0; color: "#ffffff" }
					GradientStop { position: 1.0; color: "#eeeeee" }
				}
				Flickable {
					id:aboutAreaFlickable
					anchors.fill: parent
					contentWidth: aboutArea.width
					contentHeight: aboutArea.height + aboutAreaLogo.height + 20
					flickDeceleration: Flickable.VerticalFlick
					clip:true
					Text {
						id: aboutAreatext
						width:parent.width - 20
						anchors.horizontalCenter: parent.horizontalCenter
						wrapMode: Text.WordWrap
						horizontalAlignment: Text.AlignHCenter
						font.family: "Helvetica"
						font.pointSize: 15
						text: "\nThis game is the classical Lian-Lian-Kan, also" + "know as chinese chess. Player click the two same picture can remove them, and if you remove all pictures in some time, you will win the game." + "\nGame logic is implemented with Qt " + "C++ and the UI with QML Declarative UI.\nEnjoy! =)\n\n\n\n\n\n"
					}
					Image {
						id:aboutAreaLogo
						source:"qrc:/Images/Images/s.jpg"
						anchors.horizontalCenter: parent.horizontalCenter
						anchors.top:aboutAreatext.bottom
						anchors.topMargin: 10
					}
				}
			}

			Column {
				id:menuColum
				width:parent.width - aboutArea.width - 10
				spacing:10
				Rectangle {
					id:bgmVolumeSlider
					width:parent.width
					height:30
					border.color:"gray"
					Rectangle {
						id:sliderLine
						width:parent.width - 20
						height:8
						anchors.verticalCenter: parent.verticalCenter
						color:"black"
					}
					Rectangle {
						id:sliderRect
						property int volume: 50
						property int displayvalue: volume / sliderLine.width * 100
						x:volume
						width:12
						height:bgmVolumeSlider.height - 2
						color:"gray"
						onVolumeChanged: {
							music.setBGMVolume(volume/sliderLine.width)
						}
						MouseArea {
							id:sliderMouseArea
							property int pos: 10
							anchors.fill: parent
							onContainsMouseChanged: {
								if(containsMouse)
									pos = mouseX
							}
							onPositionChanged: {
								var ret = sliderRect.volume + mouseX - pos;
								if (0 <=ret && ret <= sliderLine.width )
									sliderRect.volume = ret
							}
						}
					}
					Text {
						anchors {
							right:parent.right
							verticalCenter: parent.verticalCenter
						}
						text:sliderRect.displayvalue
					}
				}

				Button {
					id:buttonRestart
					text:"Restart Game"
					onClicked: {
						game.reStart()
						gameView.centerBoard()
						menuPanel.state = "hide"
					}
				}

				Switch {
					id: switchEffect
					textOff:"Mute"
					textOn:"Music"
					state:"on"
					onStateChanged: {
						if (state == "on") {
							music.setMute(false)
						} else {
							music.setMute(true)
						}
					}
				}
				Switch {
					id:switch3D
					textOff: "2D"
					textOn:"3D"
				}
				Button {
					id:buttonContinue
					text: game.state == Game.PAUSE ? "Continue" : "Start"
					onClicked: {
						menuPanel.state = "hide"
						if (game.state == Game.PAUSE)
							game.pauseGame(false)
						else
							game.startGame()
						music.playBGM()
					}
				}
			}
		}
	}
	states: [
		State{
			name:"hide"
			PropertyChanges {
				target: menuPanel
				opacity: 0.0
				y: -menuPanelFrame.height
			}
		}
	]
	transitions: Transition {
		NumberAnimation {
			properties: "opacity, y"
			duration: 400
		}
	}
}

