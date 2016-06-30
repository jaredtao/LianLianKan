import QtQuick 2.0
import Game 1.0
Item {
	id:tile
	width:60
	height:60

	Image{
		id:tilebackImg
		anchors.fill:parent
		fillMode: Image.Tile
		source:"qrc:/Images/Images/back.png"

		property bool tiped: modelData.tiped
		property int flicker: 0
		onFlickerChanged:  {
			if (flicker == 0) {
				modelData.tiped = false
			}
		}
		onTipedChanged: {
			if (tiped == true) {
				flicker = 1
				flickerAnimation.start()
			}
		}

		opacity: {
			if (modelData.value == 0)
				return 0.0
			else if (modelData.selected || modelData.tiped)
				return 1.0
			else
				return 0.6
		}
		Behavior on opacity {
			enabled: game.state == Game.PLAYING
			NumberAnimation {
				properties:"opacity"
				duration: 500
			}
		}

		//flicker Animation
		SequentialAnimation{
			id:flickerAnimation
			NumberAnimation {target:tilebackImg; property:"opacity"; to: 1.0; duration: 500}
			NumberAnimation {target:tilebackImg; property:"opacity"; to: 0.5; duration: 500}
			NumberAnimation {target:tilebackImg; property:"opacity"; to: 1.0; duration: 500}
			NumberAnimation {target:tilebackImg; property:"opacity"; to: 0.5; duration: 500}
			NumberAnimation {target:tilebackImg; property:"opacity"; to: 1.0; duration: 500}
			PropertyAnimation {target:tilebackImg; properties:"flicker"; to: 0;}
		}
	}
	Image {
		anchors.fill: parent
		source:"qrc:/Images/Images/" + modelData.value + ".png"
		opacity:modelData.value > 0

		Behavior on opacity {
			enabled: game.state == Game.PLAYING
			NumberAnimation {
				properties: "opacity"
				duration: 1500
			}
		}
	}
	MouseArea {
		anchors.fill: parent
		enabled: ((modelData.value > 0) && (!modelData.selected) && (!modelData.tiped))
		onClicked: {
			var ret = game.flip(index)
			if (ret == Game.DONOT) {
				music.playSelected()
			} else if (ret == Game.CLICK) {
				music.playSelected2()
				modelData.selected = true
			} else if (ret == Game.LINKED) {
				music.playLink()
			}
		}
	}
}
