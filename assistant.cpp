#include "assistant.h"
#include <algorithm>
#include <chrono>

Assistant::Assistant(QObject *parent) : QObject(parent)
{
    std::random_device device;
    gen.seed(device());
}

QVector<int> Assistant::newGame()
{
    QVector<int> tiles(100, 0);
    QVector<bool> paths(100, false);

    paths[0] = true;
    constructRoutes(tiles, paths, 0);

    int randint;
    for(int i = 0; i < 100; i++) {
        randint = gen() % 4;
        for(int j = 0; j < randint; j++)
            tiles[i] = (tiles[i] >> 1) | ((tiles[i] & 1) << 3);
    }

    return tiles;
}

QVector<bool> Assistant::lightsOn(QVector<int> tiles)
{
    QVector<bool> lights(100, false);

    lights[0] = true;
    checkLights(tiles, lights, 0);

    return lights;
}

void Assistant::constructRoutes(QVector<int> &tiles, QVector<bool> &paths, int pos) {

    QVector<int (Assistant::*)(QVector<int> &tiles, QVector<bool> &paths, int pos)> routes;

    routes.push_back(&Assistant::constructUp);
    routes.push_back(&Assistant::constructDown);
    routes.push_back(&Assistant::constructRight);
    routes.push_back(&Assistant::constructLeft);

    std::shuffle(routes.begin(), routes.end(), gen);

    int newpos;
    for(int i = 0; i < 4; i++) {
        if(-1 != (newpos = (this->*(routes[i]))(tiles, paths, pos))) {
            constructRoutes(tiles, paths, newpos);
        }
    }
}

void Assistant::checkLights(const QVector<int> &tiles, QVector<bool> &lights, int pos) {
    int row = pos / 10;
    int col = pos % 10;
    int newpos;

    newpos = pos - 10;
    if((row - 1 >= 0) && (lights[newpos] != true) &&
            ((tiles[pos] & ROUTEUP) != 0) &&
            ((tiles[newpos] & ROUTEDOWN) != 0)) {

        lights[newpos] = true;
        checkLights(tiles, lights, newpos);
    }

    newpos = pos + 10;
    if((row + 1 < 10) && (lights[newpos] != true) &&
            ((tiles[pos] & ROUTEDOWN) != 0) &&
            ((tiles[newpos] & ROUTEUP) != 0)) {

        lights[newpos] = true;
        checkLights(tiles, lights, newpos);
    }

    newpos = pos - 1;
    if((col - 1 >= 0) && (lights[newpos] != true) &&
            ((tiles[pos] & ROUTELEFT) != 0) &&
            ((tiles[newpos] & ROUTERIGHT) != 0)) {

        lights[newpos] = true;
        checkLights(tiles, lights, newpos);
    }

    newpos = pos + 1;
    if((col + 1 < 10) && (lights[newpos] != true) &&
            ((tiles[pos] & ROUTERIGHT) != 0) &&
            ((tiles[newpos] & ROUTELEFT) != 0)) {

        lights[newpos] = true;
        checkLights(tiles, lights, newpos);
    }
}

int Assistant::constructUp(QVector<int> &tiles, QVector<bool> &paths, int pos) {
    int row = pos / 10;
    int newpos = pos - 10;

    if((row - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEUP;
        tiles[newpos] += ROUTEDOWN;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int Assistant::constructDown(QVector<int> &tiles, QVector<bool> &paths, int pos) {
    int row = pos / 10;
    int newpos = pos + 10;

    if((row + 1 < 10) && (paths[newpos] != true)) {
        tiles[pos] += ROUTEDOWN;
        tiles[newpos] += ROUTEUP;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int Assistant::constructRight(QVector<int> &tiles, QVector<bool> &paths, int pos) {
    int col = pos % 10;
    int newpos = pos + 1;

    if((col + 1 < 10) && (paths[newpos] != true)) {
        tiles[pos] += ROUTERIGHT;
        tiles[newpos] += ROUTELEFT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}

int Assistant::constructLeft(QVector<int> &tiles, QVector<bool> &paths, int pos) {
    int col = pos % 10;
    int newpos = pos - 1;

    if((col - 1 >= 0) && (paths[newpos] != true)) {
        tiles[pos] += ROUTELEFT;
        tiles[newpos] += ROUTERIGHT;
        paths[newpos] = true;
        return newpos;
    }

    return -1;
}
