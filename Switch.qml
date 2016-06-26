import QtQuick 2.0

Item {
	id: toggleswitch

	width: parent.width
	height: 60

	property bool on: false
	property string textOn
	property string textOff

	state: "off"

	function toggle() {
		if (toggleswitch.state == "on")
			toggleswitch.state = "off"
		else
			toggleswitch.state = "on"
	}
	function dorelease() {
		if (knob.x == 2 && toggleswitch.state == "off")
			return

		if (knob.x == background.width - knob.width - 2 && toggleswitch.state == "on")
			return

		toggle()
	}
	Rectangle {
		id: background
		anchors.fill: parent
		border.color: "#999999"
		border.width: 1
		radius: 10
		smooth: true
		gradient: Gradient {
			GradientStop { position: 0.0; color: "#dddddd" }
			GradientStop { position: 1.0; color: "#999999" }
		}
		Text {
			id: switchTextOff
			font.family: "Helvetica"
			font.pointSize: 14
			smooth: true
			color: "#dddddd"
			anchors.verticalCenter: parent.verticalCenter
			anchors.left: parent.left
			anchors.leftMargin: knob.width/2 - switchTextOff.width/2
			text: textOff
		}
		Text {
			id: switchTextOn
			font.family: "Helvetica"
			font.pointSize: 14
			smooth: true
			color: "#dddddd"
			anchors.verticalCenter: parent.verticalCenter
			anchors.right: parent.right
			anchors.rightMargin: knob.width/2 - switchTextOn.width/2
			text: textOn
		}
		MouseArea {
			anchors.fill: parent
			onClicked: toggle()
		}
	}
	Rectangle {
		id: knob
		x: 2
		y: 2
		height: background.height - 4
		width: background.width / 2
		color: "#eeeeee"
		border.color: "#999999"
		border.width: 1
		radius: 10
		smooth: true
		gradient: Gradient {
			GradientStop { position: 0.0; color: "#666666" }
			GradientStop { position: 1.0; color: "#222222" }
		}
		Text {
			id: switchText
			font.family: "Helvetica"
			font.pointSize: 14
			smooth: true
			color: "#ffffff"
			anchors.centerIn: parent
			text: textOff
		}
		MouseArea {
			anchors.fill: parent
			drag.target: knob; drag.axis: "XAxis"
			drag.minimumX: 2
			drag.maximumX: background.width - knob.width - 2
			onClicked: toggle()
			onReleased: dorelease()
		}
	}
	states: [
		State {
			name: "on"
			PropertyChanges { target: knob; x: background.width - knob.width - 2 }
			PropertyChanges { target: toggleswitch; on: true }
			PropertyChanges { target: switchText; text: textOn }
		},
		State {
			name: "off"
			PropertyChanges { target: knob; x: 2 }
			PropertyChanges { target: toggleswitch; on: false }
			PropertyChanges { target: switchText; text: textOff }
		}
	]

	transitions: Transition {
		NumberAnimation { properties: "x"; /*easing: "easeInOutQuad";*/ duration: 200 }
	}
}
