import QtQuick 2.9
import QtQuick.Window 2.3
import QtLocation 5.9
import QtPositioning 5.8
import QtQml.Models 2.2

Map {
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    //anchors.fill: parent
    id: myMap
    width: 788
    height: 332
    plugin: mapPlugin
    center: QtPositioning.coordinate(41.2816234,69.206447)
    zoomLevel: 14


    Component.onCompleted: {
        console.log("Dimensions: ", width, height)
    }



    MapItemView {
        model: sqlModel

        delegate: MapCircle{
            id: circles
            center {
                latitude: lat;
                longitude: lon;

            }
            radius: 50.0
            color: 'red'
            border.width: 3
            opacity: 0.5
            Component.onCompleted: {
                console.count("Loaded a MapCircle")
                myMap.addMapItem(circles);
            }

            ItemSelectionModel {
                id: ism
                model: sqlModel


            }
            MouseArea {
                anchors.fill: parent
                onClicked: {

                    ism.select(sqlModel.index(index,0), ItemSelectionModel.Select | ItemSelectionModel.Current)
                    console.log(ism.hasSelection)
                }

            }
        }

    }
}
