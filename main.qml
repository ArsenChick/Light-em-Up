import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12

Window {
    id: w

    visible: true

    minimumWidth: 600
    maximumWidth: 600
    width: 600

    minimumHeight: cl.height
    maximumHeight: cl.height
    height: cl.height

    title: qsTr("Light'em Up!")

    ColumnLayout {
        id: cl

        anchors.centerIn: w.contentItem
        spacing: 2

        Gameplay {
            id: gameplay

            onVictory: {
                toolbar.stopTimer()
                message.showVictory()
            }
        }

        Toolbar {
            id: toolbar

            onNewGame: {
                gameplay.newGame()
                toolbar.resetTimer()
            }

            onTimeOut: message.showDefeat()
            onQuitApp: Qt.quit()
        }

        Messages {
            id: message

            onNewGame: {
                message.close()
                gameplay.newGame()
                toolbar.resetTimer()
            }

            onQuitApp: Qt.quit()
        }
    }
}
