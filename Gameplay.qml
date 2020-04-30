import QtQuick 2.12
import QtQuick.Layouts 1.12

GridLayout {
    id: gl

    width: 600
    height: 600

    columns: 10
    rows: 10

    columnSpacing: 0
    rowSpacing: 0

    signal victory()

    function newGame() {
        var newGameConfigs = assistant.newGame()
        for (var i = 0; i < newGameConfigs.length; i++)
            tiles.itemAt(i).config = newGameConfigs[i]
        light(newGameConfigs)
        checkWin()
    }

    function light() {
        var tileConfigs = []
        for (var i = 0; i < tiles.count; i++)
            tileConfigs.push(tiles.itemAt(i).config)
        var tileLights = assistant.lightsOn(tileConfigs)
        for (i = 0; i < tileLights.length; i++)
            tiles.itemAt(i).light = tileLights[i]
    }

    function checkWin() {
        for (var i = 0; i < tiles.count; i++) {
            if (tiles.itemAt(i).light === false)
                return
        }
        victory()
    }

    Repeater {
        id: tiles
        model: 100

        Tile {
            onRotated: {
                gl.light()
                gl.checkWin()
            }
        }
    }

    Component.onCompleted: {
        newGame()
    }
}
