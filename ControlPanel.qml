import QtQuick 2.0

Item {
	id:controlPanel
	width:180
	height:parent.height

	Item {
		id:rotabelPanel
		width:parent.width
		height: 300
		transformOrigin: Item.Center

		Frame {
			id:box1
			height:80
			y:10
			Text {
				x:25
				y:5
				font.family: "Helvetica"
				font.pointSize: 12
				smooth:true
				color:"black"
				text:"Time"
			}
			Text {
				anchors.right: parent.right
				anchors.rightMargin: 15
				y:5
				font.family: "Helvetica"
				font.pointSize: 12
				smooth:true
				color:"black"
				text:"Score"
			}
			Text{
				x:10
				y:25
				font.family: "Helvetica"
				font.pointSize: 26
				smooth:true
				color:"gray"
				style: Text.Outline
				styleColor:"black"
				text:game.gametime
			}
			Text {
				anchors.right: parent.right
				anchors.rightMargin: 20
				y:25
				font.family: "Helvetica"
				font.pointSize: 26
				smooth:true
				color:"gray"
				style: Text.Outline
				styleColor:"black"
				text:game.score
			}
		}
		Frame {
			id: box2
			height: 320
			anchors.top: box1.bottom
			anchors.topMargin: 10
			Image{
				id:imageControlLogo
				anchors.top: parent.top
				anchors.topMargin: 10
				anchors.horizontalCenter: parent.horizontalCenter
				source:"qrc:/Images/Images/icon.png"
			}
			Text {
				id:levelText
				anchors.top: imageControlLogo.bottom
				anchors.horizontalCenter: parent.horizontalCenter
				font.family: "Helvetica"
				font.pointSize: 24
				smooth: true
				color: "white"
				style: Text.Outline
				styleColor: "black"
				text:"Level: " + game.level;
			}

			Text {
				anchors.top: levelText.bottom
				anchors.topMargin: 10
				anchors.horizontalCenter: parent.horizontalCenter
				font.family: "Helvetica"
				font.pointSize: 24
				smooth: true
				color: "white"
				style: Text.Outline
				styleColor: "black"
				text:"Hint: " + game.tip;
			}
			Button {
				id:buttonHint
				height:60
				width:parent.width - 20
				anchors.bottom: parent.bottom
				anchors.bottomMargin: 10
				anchors.horizontalCenter: parent.horizontalCenter
				text:"Hint"
				opacity:game.state != game.PAUSE
				disabled: game.tip <=0
				onClicked: {

				}
			}
			Text {
				anchors.centerIn: buttonHint
				font.family: "Helvetica"
				font.pointSize: 42
				smooth: true
				color: "white"
				style: Text.Outline
				styleColor: "black"
				text: "Wins!"
				opacity: !game.state == game.WIN
			}
		}
		Frame {
			id:box3
			height:80
			anchors.top: box2.bottom
			anchors.topMargin: 10

			Button {
				id:buttonMainMenu
				width:parent.width - 20

				anchors.centerIn: parent
				text:"Main Menu"
				onClicked: {
					menuPanel.state = ""
					game.pauseGame(true)
				}
			}
		}
	}
}
