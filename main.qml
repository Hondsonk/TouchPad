import QtQuick 2.3
import QtQuick.Window 2.2

// Swipe concepts taken from: https://gist.github.com/gsantner/bb0d98ea0616f82f484ab2b99ff99527
Window
{
    signal clicked
    signal doubleClicked
    signal pan(int dx, int dy)
    signal swipe(string direction, int distance)
    signal windowSizeChanged(int width, int height)

    property int resolution: width*height

    id: window
    objectName: "window"
    visible: true
    width: 320
    height: 240
    onResolutionChanged: windowSizeChanged(width, height)
    title: qsTr("Touch Pad")

    Rectangle
    {
        id: touchPad
        color: "black"
        anchors.fill: parent

        MouseArea
        {
            property int swipeThreshold: 5

            readonly property string dirUp: "up"
            readonly property string dirDown: "down"
            readonly property string dirLeft: "left"
            readonly property string dirRight: "right"

            property point lastPos: Qt.point(-1, -1)
            property int xProjectionRatio: 640 / touchPad.width
            property int yProjectionRatio: 480 / touchPad.height

            anchors.fill: parent

            onPressed:
            {
                drag.axis = Drag.XAndYAxis
                lastPos = Qt.point(mouse.x, mouse.y)
            }

            onClicked:
            {
                window.clicked();
            }

            onDoubleClicked:
            {
                window.doubleClicked();
            }

            onPositionChanged:
            {
                if (lastPos.x > -1)
                {
                    switch (drag.axis)
                    {
                    case Drag.XAndYAxis:
                        //console.log("(", Math.abs(mouse.x - lastPos.x), ",", Math.abs(mouse.y - lastPos.y), ")" );
                        if (Math.abs(mouse.x - lastPos.x) > swipeThreshold)
                            drag.axis = Drag.XAxis
                        else if ( Math.abs(mouse.y - lastPos.y) > swipeThreshold)
                            drag.axis = Drag.YAxis
                        break

                    //case Drag.XAxis: window.pan(mouse.x - lastPos.x, 0); break
                    //case Drag.YAxis: window.pan(0, mouse.y - lastPos.y); break
                    }

                    window.pan(mouse.x - lastPos.x, mouse.y - lastPos.y);

                }
                lastPos = Qt.point(mouse.x, mouse.y)

/*
                if (lastPos.x > -1)
                {
                    var deltaX = mouse.x-lastPos.x;
                    var deltaY = mouse.y-lastPos.y;
                    window.pan(deltaX, deltaY);
                    //console.log(deltaX, deltaY);
                }
                lastPos = Qt.point(mouse.x, mouse.y);
                */

            }
            onReleased:
            {
                lastPos = Qt.point(-1, -1)

                switch (drag.axis)
                {
                case Drag.XAndYAxis: canceled(mouse); break
                case Drag.XAxis: window.swipe(mouse.x - lastPos.x < 0 ? dirLeft : dirRight, Math.abs(mouse.x - lastPos.x)); break
                case Drag.YAxis: window.swipe(mouse.y - lastPos.y < 0 ? dirUp: dirDown, Math.abs(mouse.y - lastPos.y)); break
                }
            }
        }
    }
}
