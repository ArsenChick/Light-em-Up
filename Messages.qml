import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3

MessageDialog {
    id: msg

    function showDefeat() {
        msg.text = "You lose! Continue?"
        msg.open()
    }

    function showVictory() {
        msg.text = "You win! Continue?"
        msg.open()
    }

    signal newGame()
    signal quitApp()

    standardButtons: StandardButton.Yes | StandardButton.No
    onYes: newGame()
    onNo: quitApp()
}
