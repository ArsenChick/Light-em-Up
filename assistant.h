#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <QObject>
#include <QVector>
#include <random>

#define ROUTEUP 8
#define ROUTELEFT 4
#define ROUTEDOWN 2
#define ROUTERIGHT 1

class Assistant : public QObject
{
    Q_OBJECT
public:
    explicit Assistant(QObject *parent = nullptr);

signals:

public slots:
    QVector<int> newGame();
    QVector<bool> lightsOn(QVector<int> tiles);


private:
    void constructRoutes(QVector<int> &tiles, QVector<bool> &paths, int pos);
    void checkLights(const QVector<int> &tiles, QVector<bool> &lights, int pos);

    int constructUp(QVector<int> &tiles, QVector<bool> &paths, int pos);
    int constructDown(QVector<int> &tiles, QVector<bool> &paths, int pos);
    int constructRight(QVector<int> &tiles, QVector<bool> &paths, int pos);
    int constructLeft(QVector<int> &tiles, QVector<bool> &paths, int pos);

    std::mt19937 gen;
};


#endif // ASSISTANT_H
