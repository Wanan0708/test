#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <synchapi.h>
#include <QCoreApplication>
#include <QTimer>

class Elevator : public QObject
{
    Q_OBJECT
public:
    Elevator();
//    ~Elevator();

public:
    void eUp(int);
    void eDown(int);
    bool eOpen();
    bool eClose();
    void eMoveTo(int);

public:
    int eId;
    int currentFloor;
    bool opening;
    bool closeing;
    bool uping;
    bool downing;
    bool running;
    bool idleing;
    bool opened;
    bool closed;
    int peopleCount;
    int weight;

signals:
    void floorChanged();
};

#endif // ELEVATOR_H
