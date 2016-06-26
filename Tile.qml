import QtQuick 2.0

Item {
	id:tile
	width:60
	height:60
	Image{
		anchors.fill:parent
		fillMode: Image.Tile
		source:"qrc:/Images/Images/back.png"
		opacity: 0.6
	}
	Image {
		anchors.fill: parent
//		fillMode: Image.Tile
		source:"qrc:/Images/Images/1.png"
	}
}
