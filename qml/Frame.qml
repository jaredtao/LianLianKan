import QtQuick 2.0

Rectangle {
	width:parent.width
	height:parent.height
	border.color: "#999999"
	border.width: 2
	radius:10
	smooth:true
	gradient: Gradient {
		GradientStop {position: 0.0; color:"#ffffff"}
		GradientStop {position: 1.0; color:"#dddddd"}
	}

	MouseArea {
		anchors.fill: parent
		onClicked: {
			// This will just block clicks inside frame for not going into board
		}
	}
}
