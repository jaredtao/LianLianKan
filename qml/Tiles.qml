import QtQuick 2.0

Item {
	id:tile
	width:60
	height:60

	Image{
		anchors.fill:parent
		fillMode: Image.Tile
		source:"qrc:/Images/Images/back.png"
		opacity: {
			if (modelData.value == 0)
				return 0.0
			else if (modelData.selected)
				return 1.0
			else
				return 0.6
		}
		Behavior on opacity {
			enabled: game.state == game.PLAYING
			NumberAnimation {
				properties:"opacity"
				duration: 500
			}
		}
	}
	Image {
		anchors.fill: parent
		source:"qrc:/Images/Images/" + modelData.value + ".png"
		opacity:modelData.value > 0

		Behavior on opacity {
			enabled: game.state == game.PLAYING
			NumberAnimation {
				properties: "opacity"
				duration: 1500
			}
		}
	}
	MouseArea {
		anchors.fill: parent
		enabled: ((modelData.value > 0) && (!modelData.selected))
		onClicked: {
			var ret = game.flip(index)
			if (ret == game.DONOT) {
				music.playSelected()
			} else if (ret == game.CLICK) {
				music.playSelected2()
				modelData.selected = true
			} else if (ret == game.LINKED) {
				music.playLink()
			}
			console.log("clicked" + ret)
		}
	}
}
