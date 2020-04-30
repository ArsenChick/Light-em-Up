import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {
    id: rl

    signal newGame()
    signal quitApp()
    signal timeOut()

    property int timeLimit: 120

    function resetTimer() {
        timer.time = rl.timeLimit
        timer.restart()
    }

    function stopTimer() {
        timer.stop()
    }

    Button {
        id: newGameButton

        text: "New Game"
        onClicked: newGame()
    }

    TextField {
        id: timerField

        Layout.fillWidth: true

        Timer {
            id: timer
            interval: 1000
            running: true
            repeat: true

            property int time: rl.timeLimit

            triggeredOnStart: true
            onTriggered: {
                timer.time -= 1

                var timestr = timer.time.toString()
                timerField.text = "Time left: " + timestr

                if (timer.time == 0) {
                    timer.running = false
                    timeOut()
                }
            }
        }
    }

    Button {
        id: quitButton

        text: "Quit"
        onClicked: quitApp()
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequences: ["Ctrl+N"]
        onActivated: newGame()
    }

    Shortcut {
        context: Qt.ApplicationShortcut
        sequences: [StandardKey.Close, "Ctrl+Q"]
        onActivated: quitApp()
    }
}
