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
			if(modelData.selected)
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
		source:"qrc:/Images/Images/" +modelData.value + ".png"
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
		enabled: modelData.value !== 0 && !modelData.selected || !modelData.tiped
		onClicked: {
			var ret = game.flip(index)
			if (ret == -1)
				music.playSelected()
			else if (ret == 1)
				music.playSelected2()
			else if (ret == 0)
				music.playLink()
		}
	}
}
