import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import OSGQuick.OSGView 1.0

Window {
	id:mainWindow;
    visible: true;
    width: 640;
    height: 480;
	color: "black";
    title: qsTr("OSG嵌入QQuick");
	OSGView
	{
		id:view;
		anchors.fill: parent;
		focus:true;
	}
}
