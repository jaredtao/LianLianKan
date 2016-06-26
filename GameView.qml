import QtQuick 2.0

Item {
	id:gameView
	anchors.fill: parent
	// Function to center the board when starting new game
	function centerBoadr() {
		centeringAnimation.start();
	}
	 // *** Background image ***
	Image {
		id:backgroundImage
		source:"qrc:/Images/Images/backgrand.jpg"
		// Make the background "parallax scrolling"
		x: -gameView.width/8.0 - boardFlickable.contentX/4.0
		y: -gameView.height/8.0 - boardFlickable.contentY/4.0
	}
	// *** Board ***
	Flickable {
		id: boardFlickable
		anchors.fill: parent
		contentWidth:boardFlickable.width + controlPanel.width + 40 + 10
		contentHeight: boardFlickable.height + 40
		maximumFlickVelocity:  500
		flickDeceleration: 1000
//		transform: [
//			Rotation {
//				origin.x: gameView.width / 2
//				origin.y: gameView.height / 2
//				axis: {x: 1; y: 0; z: 0}
//				angle: Math.min(Math.max(-boardFlickable.verticalVelocity / 4, -75), 75)
//				Behavior on angle {SpringAnimation {spring: 1.5; damping: 0.75} }
//			},
//			Rotation {
//				origin.x: gameView.width / 2
//				origin.y: gameView.height / 2
//				axis {x:0; y:1; z:0}
//				angle:Math.min(Math.max(boardFlickable.horizontalVelocity / 4, -75), 75)
//				Behavior on angle { SpringAnimation { spring: 1.5; damping: 0.75 } }
//			}
//		]
		Grid {
			id : boardGrid
			columns:10
			spacing:2
			x:50
			y:50
			Repeater {
				model:100
				Tile {}
			}
		}
	}
	ControlPanel {
		id:controlPanel
		anchors.right: boardFlickable.right
		anchors.rightMargin: 10
	}
}
